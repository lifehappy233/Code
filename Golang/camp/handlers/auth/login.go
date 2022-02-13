package auth

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

func Login(c *gin.Context) { // /api/v1/auth/login
	var req types.LoginRequest
	var res types.LoginResponse
	c.BindJSON(&req)

	var member model.Member

	// UserHasDeleted     ErrNo = 3  // 用户已删除
	// UserNotExisted     ErrNo = 4  // 用户不存在
	// WrongPassword      ErrNo = 5  // 密码错误
	if err := model.Db.First(&member, "username = ?", req.Username).Error; err != nil {
		res.Code = 4
	} else if !member.Isactive {
		res.Code = 3
	} else if req.Password != member.Password {
		res.Code = 5
	}
	if res.Code == 0 {
		res.Data.UserID = fmt.Sprintf("%d", member.Userid)
		session := sessions.Default(c)
		session.Set("userid", member.Userid)
		session.Set("nickname", member.Nickname)
		session.Set("username", req.Username)
		session.Set("usertype", member.Usertype)
		session.Save()
	}
	c.JSON(http.StatusOK, res)
}
