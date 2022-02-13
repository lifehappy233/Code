package model

import (
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
)

const dsn = "root:lifehappy01@tcp(127.0.0.1:3306)/gormlearn?charset=utf8mb4&parseTime=True&loc=Local"

var Db *gorm.DB

func init() {
	Db, _ = gorm.Open(mysql.Open(dsn), &gorm.Config{})
	Db.AutoMigrate(&Member{}, &Student{}, &Teacher{}, &Course{}, &StudentCourse{})

	// 系统内置管理员账号, 账号名：JudgeAdmin 密码：JudgePassword2022
	Db.Create(Member{
		Nickname: "JudgeAdmin",
		Username: "JudgeAdmin",
		Password: "JudgePassword2022",
		Usertype: 1,
	})

	// 在teacher表中加入一个空老师，没有任课老师的课程默认配置。
	Db.Create(Teacher{
		Teacherid:   1,
		Teachername: "JudgeAdmin",
	})
}
