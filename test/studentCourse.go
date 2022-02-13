package model

type StudentCourse struct {
	Student     *Student
	Studentid   uint32 `gorm:"primary_key"`
	Studentname string `gorm:"size:30"`

	Course     *Course
	Courseid   uint32 `gorm:"primary_key"`
	Coursename string `gorm:"size:30"`
}

func (StudentCourse) TableName() string {
	return "student_course"
}
