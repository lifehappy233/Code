package teacher

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/go-redis/redis/v8"
)

// CourseNotExisted   ErrNo = 12 // 课程不存在
// CourseHasBound     ErrNo = 8  // 课程已绑定过

func BindCourse(c *gin.Context) { // /api/v1/teacher/bind_course
	var req types.BindCourseRequest
	c.BindJSON(&req)
	var res types.BindCourseResponse
	var course model.Course
	if err := model.Db.First(&course, "course_id = ?", req.CourseID).Error; err != nil { // not find
		res.Code = types.CourseNotExisted
	} else if course.Teacherid != 0 {
		res.Code = types.CourseHasBound
	} else {
		model.Db.Model(&model.Course{}).Where("course_id = ?", req.CourseID).Update("teacher_id", req.TeacherID)
		model.Rdb.Set(model.Ctx, fmt.Sprintf("courseteacher%d", course.Courseid), req.TeacherID, redis.KeepTTL)
	}
	c.JSON(http.StatusOK, res)
}

// type BindCourseRequest struct {
// 	CourseID  string `json:"CourseID" form:"CourseID"`
// 	TeacherID string `json:"TeacherID" form:"TeacherID"`
// }

// type BindCourseResponse struct {
// 	Code ErrNo
// }
