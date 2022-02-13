package member

import (
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// UserHasDeleted     ErrNo = 3  // 用户已删除
// UserNotExisted     ErrNo = 4  // 用户不存在

func Getmember(c *gin.Context) { // /api/v1/member
	var req types.GetMemberRequest
	c.BindQuery(&req)
	var res types.GetMemberResponse
	var member model.Member
	if err := model.Db.First(&member, "user_id = ?", req.UserID).Error; err != nil { // not find
		res.Code = types.UserNotExisted
	} else if !member.Isactive {
		res.Code = types.UserHasDeleted
	} else {
		res.Data = types.TMember{
			UserID:   req.UserID,
			Nickname: member.Nickname,
			Username: member.Username,
			UserType: types.UserType(member.Usertype),
		}
	}
	c.JSON(http.StatusOK, res)
}
