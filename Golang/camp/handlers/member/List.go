package member

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// ParamInvalid       ErrNo = 1  // 参数不合法

func List(c *gin.Context) { // /api/v1/member/list
	var req types.GetMemberListRequest
	req.Limit, req.Offset = -1, -1
	c.BindQuery(&req)
	fmt.Println(req.Offset, req.Limit)
	var res types.GetMemberListResponse
	if req.Limit != -1 && req.Offset != -1 {
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
	} else {
		res.Code = types.ParamInvalid
	}
	c.JSON(http.StatusOK, res)
}
