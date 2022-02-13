package main

import (
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
)

type Course struct {
	Courseid   uint32 `gorm:"primaryKey;column:course_id"`
	Coursename string `gorm:"column:course_name"`
	Cap        uint32 `gorm:"column:cap"`
	Remaincap  uint32 `gorm:"column:remain_cap"`
	Teacherid  uint32 `gorm:"column:teacher_id"`
}

func (Course) TableName() string {
	return "course"
}
func main() {
	// data source name
	dsn := "root:lifehappy01@tcp(127.0.0.1:3306)/learn?charset=utf8mb4&parseTime=True&loc=Local"
	db, _ := gorm.Open(mysql.Open(dsn), &gorm.Config{})
	db.Model(&Course{}).Where("course_id = ?", "1000002").Update("remain_cap", gorm.Expr("remain_cap - ?", 1))
	// if err := db.First(&Course{}, "course_name = ?", "111").Error; err == nil { // not find
	// 	fmt.Println("true")
	// }
	// fmt.Println("false")
}
