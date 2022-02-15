package teacher

import (
	"fmt"
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

// UnknownError ErrNo = 255 // 未知错误

func GetCourse(c *gin.Context) { // /api/v1/teacher/get_course
	var req types.GetTeacherCourseRequest
	c.BindQuery(&req)
	var res types.GetTeacherCourseResponse
	if err := model.Db.First(&model.Teacher{}, "teacher_id = ?", req.TeacherID).Error; err != nil {
		res.Code = types.UnknownError
	} else {
		var courses []model.Course
		model.Db.Where("teacher_id = ?", req.TeacherID).Find(&courses)
		for _, course := range courses {
			res.Data.CourseList = append(res.Data.CourseList, &types.TCourse{
				CourseID:  fmt.Sprintf("%d", course.Courseid),
				Name:      course.Coursename,
				TeacherID: req.TeacherID,
			})
		}
	}
	c.JSON(http.StatusOK, res)
}

// type GetTeacherCourseRequest struct {
// 	TeacherID string `json:"TeacherID" form:"TeacherID"`
// }

// type GetTeacherCourseResponse struct {
// 	Code ErrNo
// 	Data struct {
// 		CourseList []*TCourse
// 	}
// }
