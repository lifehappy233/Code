package model

type Teacher struct {
	Teacherid   uint32 `gorm:"primary_key"`
	Teachername string `gorm:"unique;size:30"`
}

func (Teacher) TableName() string {
	return "teacher"
}
