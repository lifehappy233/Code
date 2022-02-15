package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

// type Course struct {
// 	Courseid   uint32 `gorm:"primaryKey;column:course_id"`
// 	Coursename string `gorm:"column:course_name"`
// 	Cap        uint32 `gorm:"column:cap"`
// 	Remaincap  uint32 `gorm:"column:remain_cap"`
// 	Teacherid  uint32 `gorm:"column:teacher_id"`
// }

// func (Course) TableName() string {
// 	return "course"
// }

type ScheduleCourseRequest struct {
	TeacherCourseRelationShip map[string][]string `form:"TeacherCourseRelationShip" json:"TeacherCourseRelationShip"`
	// key 为 teacherID , val 为老师期望绑定的课程 courseID 数组
}

func main() {
	router := gin.Default()
	router.GET("/test", func(c *gin.Context) {
		var res ScheduleCourseRequest
		res.TeacherCourseRelationShip["name"] = append(res.TeacherCourseRelationShip["name"], "value1")
		c.JSON(http.StatusOK, res)
	})
	router.Run(":8090")
	// data source name
	// dsn := "root:lifehappy01@tcp(127.0.0.1:3306)/learn?charset=utf8mb4&parseTime=True&loc=Local"
	// db, _ := gorm.Open(mysql.Open(dsn), &gorm.Config{})
	// db.Model(&Course{}).Where("course_id = ?", "1000002").Update("remain_cap", gorm.Expr("remain_cap - ?", 1))
	// if err := db.First(&Course{}, "course_name = ?", "111").Error; err == nil { // not find
	// 	fmt.Println("true")
	// }
	// fmt.Println("false")
}
