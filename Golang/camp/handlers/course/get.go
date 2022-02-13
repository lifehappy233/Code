package course

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// CourseNotExisted   ErrNo = 12 // 课程不存在

func Get(c *gin.Context) { // /api/v1/course/get
	var req types.GetCourseRequest
	c.BindQuery(&req)
	var res types.GetCourseResponse
	var course model.Course
	if err := model.Db.First(&course, "course_id = ?", req.CourseID).Error; err != nil { // not find
		res.Code = types.CourseNotExisted
	} else {
		res.Data = types.TCourse{
			CourseID: fmt.Sprintf("%d", course.Courseid),
			Name:     course.Coursename,
		}
		if course.Teacherid == 0 {
			res.Data.TeacherID = "-1"
		} else {
			res.Data.TeacherID = fmt.Sprintf("%d", course.Teacherid)
		}
	}
	c.JSON(http.StatusOK, res)
}

// type GetCourseRequest struct {
// 	CourseID string `json:"CourseID" form:"CourseID"`
// }

// type GetCourseResponse struct {
// 	Code ErrNo
// 	Data TCourse
// }
