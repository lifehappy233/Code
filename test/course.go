package model

type Course struct {
	Courseid    uint32 `gorm:"primary_key"`
	Coursename  string `gorm:"unique;size:30"`
	Cap         uint32
	Remaincap   uint32
	Teacher     *Teacher
	Teacherid   uint32 `gorm:"default=1"`
	Teachername string `gorm:"size:30;default=JudgeAdmin"`
}

func (Course) TableName() string {
	return "course"
}
