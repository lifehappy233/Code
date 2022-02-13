package member

import (
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// UserHasDeleted     ErrNo = 3  // 用户已删除
// UserNotExisted     ErrNo = 4  // 用户不存在
// ParamInvalid       ErrNo = 1  // 参数不合法

func Update(c *gin.Context) { // /api/v1/member/update
	var req types.UpdateMemberRequest
	c.BindJSON(&req)
	var res types.UpdateMemberResponse
	var member model.Member
	if err := model.Db.First(&member, "user_id = ?", req.UserID).Error; err != nil { // not find
		res.Code = types.UserNotExisted
	} else if !member.Isactive {
		res.Code = types.UserHasDeleted
	} else {
		nicknamelen := len(req.Nickname)
		if nicknamelen < 4 || nicknamelen > 20 {
			res.Code = types.ParamInvalid
		} else {
			model.Db.Model(&model.Member{}).Where("user_id = ?", req.UserID).Update("nickname", req.Nickname)
		}
	}
	c.JSON(http.StatusOK, res)
}
