package teacher

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/go-redis/redis/v8"
)

// CourseNotBind      ErrNo = 9  // 课程未绑定过
// CourseNotExisted   ErrNo = 12 // 课程不存在
// UnknownError ErrNo = 255 // 未知错误

func UnbindCourse(c *gin.Context) { // /api/v1/teacher/unbind_course
	var req types.UnbindCourseRequest
	c.BindJSON(&req)
	var res types.UnbindCourseResponse
	var course model.Course
	if err := model.Db.First(&course, "course_id = ?", req.CourseID).Error; err != nil { // not find
		res.Code = types.CourseNotExisted
	} else if course.Teacherid == 0 {
		res.Code = types.CourseNotBind
	} else if fmt.Sprintf("%d", course.Teacherid) != req.TeacherID {
		res.Code = types.UnknownError
	} else {
		model.Db.Model(&model.Course{}).Where("course_id = ?", req.CourseID).Update("teacher_id", 0)
		model.Rdb.Set(model.Ctx, fmt.Sprintf("courseteacher%d", course.Courseid), 0, redis.KeepTTL)
	}
	c.JSON(http.StatusOK, res)
}

// type UnbindCourseRequest struct {
// 	CourseID  string `json:"CourseID" form:"CourseID"`
// 	TeacherID string `json:"TeacherID" form:"TeacherID"`
// }

// type UnbindCourseResponse struct {
// 	Code ErrNo
// }
