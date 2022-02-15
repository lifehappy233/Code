package member

import (
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// UserNotExisted     ErrNo = 4  // 用户不存在
// UserHasDeleted     ErrNo = 3  // 用户已删除

func Delete(c *gin.Context) { // /api/v1/member/delete
	var req types.DeleteMemberRequest
	c.BindJSON(&req)
	var res types.DeleteMemberResponse
	var member model.Member
	if err := model.Db.First(&member, "user_id = ?", req.UserID).Error; err != nil { // not find
		res.Code = types.UserNotExisted
	} else if member.Isactive {
		model.Db.Model(&model.Member{}).Where("user_id = ?", req.UserID).Update("is_active", 0)
	} else {
		res.Code = types.UserHasDeleted
	}
	c.JSON(http.StatusOK, res)
}
