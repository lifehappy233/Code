package member

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

func List(c *gin.Context) { // /api/v1/member/list
	var req types.GetMemberListRequest
	c.BindQuery(&req)
	var res types.GetMemberListResponse
	var members []model.Member
	model.Db.Offset(req.Offset).Limit(req.Limit).Where("is_active = ?", true).Find(&members)
	for _, member := range members {
		res.Data.MemberList = append(res.Data.MemberList, types.TMember{
			UserID:   fmt.Sprintf("%d", member.Userid),
			Nickname: member.Nickname,
			Username: member.Username,
			UserType: types.UserType(member.Usertype),
		})
	}
	c.JSON(http.StatusOK, res)
}
