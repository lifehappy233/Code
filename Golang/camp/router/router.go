package router

import (
	"lifehappy/camp/handlers/auth"
	"lifehappy/camp/handlers/course"
	"lifehappy/camp/handlers/member"
	"lifehappy/camp/handlers/student"
	"lifehappy/camp/handlers/teacher"

	"github.com/gin-contrib/sessions"
	"github.com/gin-contrib/sessions/cookie"
	"github.com/gin-gonic/gin"
)

func RegisterRouter(r *gin.Engine) {
	g := r.Group("/api/v1")

	store := cookie.NewStore([]byte("secret2333"))
	g.Use(sessions.Sessions("camp-session", store))

	g.GET("/auth/test", auth.Test) // 测试cookie是否成功设置，查看当前账号的信息

	// 成员管理
	g.POST("/member/create", member.Creater) // ok
	g.GET("/member", member.Getmember)       // ok
	g.GET("/member/list", member.List)       // ok
	g.POST("/member/update", member.Update)  // ok
	g.POST("/member/delete", member.Delete)  // ok

	// 登录

	g.POST("/auth/login", auth.Login)   // ok
	g.POST("/auth/logout", auth.Logout) // ok
	g.GET("/auth/whoami", auth.Whoami)  // ok

	// 排课
	g.POST("/course/create", course.Create) // ok
	g.GET("/course/get", course.Get)        // ok

	g.POST("/teacher/bind_course", teacher.BindCourse)     // ok
	g.POST("/teacher/unbind_course", teacher.UnbindCourse) // ok
	g.GET("/teacher/get_course", teacher.GetCourse)        // ok
	g.POST("/course/schedule", teacher.Schedule)           // ok

	// 抢课
	g.POST("/student/book_course", student.BookCourse)
	g.GET("/student/course", student.Course)

}
