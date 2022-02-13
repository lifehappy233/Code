package course

import (
	"lifehappy/camp/model"
	"lifehappy/camp/types"
	"net/http"

	"github.com/gin-gonic/gin"
)

func Create(c *gin.Context) { // /api/v1/course/create
	var req types.CreateCourseRequest
	c.BindJSON(&req)
	var res types.CreateCourseResponse
	flag := model.Course{}.CoursenameUsed(req.Name)
	if flag {
		res.Code = types.UnknownError
	} else {
		res.Data.CourseID = model.Course{}.Insert(req)
	}
	c.JSON(http.StatusOK, res)
}

// type CreateCourseRequest struct {
// 	Name string `json:"Name" form:"Name"`
// 	Cap  int    `json:"Cap" form:"Cap"`
// }

// type CreateCourseResponse struct {
// 	Code ErrNo
// 	Data struct {
// 		CourseID string
// 	}
// }
