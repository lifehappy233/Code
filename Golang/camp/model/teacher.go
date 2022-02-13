package model

type Teacher struct {
	Teacherid   uint32 `gorm:"primaryKey;column:teacher_id"`
	Teachername string `gorm:"column:teacher_name"`
}

func (Teacher) TableName() string {
	return "teacher"
}

func (Teacher) Insert(teacherid uint32, teachername string) {
	Db.Create(Teacher{Teacherid: teacherid, Teachername: teachername})
}
