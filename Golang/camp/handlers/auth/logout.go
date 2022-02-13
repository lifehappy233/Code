package auth

import (
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

func Logout(c *gin.Context) { // /api/v1/auth/logout
	session := sessions.Default(c)
	session.Clear()
	session.Save()
	c.JSON(http.StatusOK, types.LogoutResponse{Code: 0})
}
