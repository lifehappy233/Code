package model

import (
	"fmt"
	"lifehappy/camp/types"
)

type Member struct {
	Userid   uint32 `gorm:"column:user_id;primaryKey"`
	Nickname string `gorm:"column:nickname"`
	Username string `gorm:"column:username"`
	Password string `gorm:"column:password"`
	Usertype uint8  `gorm:"column:user_type"`
	Isactive bool   `gorm:"column:is_active"`
}

func (Member) TableName() string {
	return "member"
}

func (Member) Insert(req types.CreateMemberRequest) string {
	member := Member{
		Nickname: req.Nickname,
		Username: req.Username,
		Password: req.Password,
		Usertype: uint8(req.UserType),
		Isactive: true,
	}
	Db.Create(&member)
	if req.UserType == 2 { // 学生表插入
		Student{}.Insert(member.Userid, member.Username)
	} else if req.UserType == 3 { // 教师表插入
		Teacher{}.Insert(member.Userid, member.Username)
	}
	return fmt.Sprintf("%d", member.Userid)
}

func (Member) UsernameUsed(username string) bool {
	if err := Db.First(&Member{}, "username = ?", username).Error; err == nil { // find
		return true
	}
	return false
}
