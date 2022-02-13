package auth

import (
	"fmt"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

// LoginRequired      ErrNo = 6  // 用户未登录

func Whoami(c *gin.Context) { // /api/v1/auth/whoami
	session := sessions.Default(c)
	var res types.WhoAmIResponse
	if val := session.Get("userid"); val == nil {
		res.Code = types.LoginRequired
	} else {
		// fmt.Printf("%T %T %T %T\n", session.Get("userid"), session.Get("username"), session.Get("nickname"), session.Get("usertype"))
		userid := session.Get("userid")
		nickname := session.Get("nickname")
		username := session.Get("username")
		usertype := session.Get("usertype").(uint8)
		res.Data = types.TMember{
			UserID:   fmt.Sprintf("%d", userid),
			Nickname: fmt.Sprintf("%s", nickname),
			Username: fmt.Sprintf("%s", username),
			UserType: types.UserType(usertype),
		}
	}
	c.JSON(http.StatusOK, res)
}
