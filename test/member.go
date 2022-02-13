package model

type Member struct {
	Userid   uint32 `gorm:"primary_key"`
	Nickname string `gorm:"size:30"`
	Username string `gorm:"size:30;unique"`
	Password string `gorm:"size:30"`
	Usertype uint8
	Isactive bool `gorm:"default=true"`
}

func (Member) TableName() string {
	return "member"
}
