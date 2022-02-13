package model

type Student struct {
	Studentid   uint32 `gorm:"primary_key"`
	Studentname string `gorm:"unique;size:30"`
}

func (Student) TableName() string {
	return "student"
}
