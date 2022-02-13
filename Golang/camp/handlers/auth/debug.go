package auth

import (
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

func Test(c *gin.Context) { // /api/v1/auth/test
	session := sessions.Default(c)
	c.String(http.StatusOK, "%v %v %v", session.Get("userid"), session.Get("username"), session.Get("usertype"))
}
