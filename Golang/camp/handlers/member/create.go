package member

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"
	"regexp"

	"github.com/gin-contrib/sessions"
	"github.com/gin-gonic/gin"
)

var testUsername = regexp.MustCompile(`^[a-zA-Z]*$`)

var testPassword = regexp.MustCompile(`^[a-zA-Z0-9]{8,20}$`)
var passwordLower = regexp.MustCompile(`^.*?[a-z]+.*?$`)
var passwordUpper = regexp.MustCompile(`^.*?[A-Z]+.*?$`)
var passwordNumber = regexp.MustCompile(`^.*?[0-9]+.*?$`)

func isAllLetter(str []byte) bool {
	return testUsername.Match(str)
}

func judgePassword(str []byte) bool {
	return testPassword.Match(str) && passwordLower.Match(str) && passwordUpper.Match(str) && passwordNumber.Match(str)
}

// ParamInvalid       ErrNo = 1  // 参数不合法
// UserHasExisted     ErrNo = 2  // 该 Username 已存在
// PermDenied         ErrNo = 10 // 没有操作权限

func Creater(c *gin.Context) { //  /api/v1/member/create
	var req types.CreateMemberRequest
	var res types.CreateMemberResponse
	c.BindJSON(&req)

	fmt.Println(req, res)

	var nicknameLen, usernameLen = len(req.Nickname), len(req.Username)

	// 检查当前登入用户是否是管理员账号，PermDenied
	session := sessions.Default(c)
	if session.Get("usertype") != uint8(1) {
		fmt.Println(session.Get("usertype"))
		res.Code = types.PermDenied
	}
	fmt.Println(nicknameLen, usernameLen)
	// 检查 UserType 是否在 1 ～ 3，nickname, username长度是否合法
	if res.Code == 0 && (req.UserType < 1 || req.UserType > 3 || nicknameLen < 4 || nicknameLen > 20 || usernameLen < 8 || usernameLen > 20) {
		res.Code = types.ParamInvalid
	}

	fmt.Println(res.Code, "111")

	// username是否只有大小写字母
	if res.Code == 0 && !isAllLetter([]byte(req.Username)) {
		res.Code = types.ParamInvalid
	}

	fmt.Println(res.Code, "222")

	// password是否同时含有大小写字母、数字，以及长度是否合法
	if res.Code == 0 && !judgePassword([]byte(req.Password)) {
		res.Code = types.ParamInvalid
	}

	fmt.Println(res.Code, "333")

	// username 唯一性，判断用户名是否存在
	judge := model.Member{}.UsernameUsed(req.Username)
	if res.Code == 0 && judge {
		res.Code = types.UserHasExisted
	}

	fmt.Println(res.Code, "444")

	if res.Code == 0 {
		res.Data.UserID = model.Member{}.Insert(req)
	}

	c.JSON(http.StatusOK, res)
}
