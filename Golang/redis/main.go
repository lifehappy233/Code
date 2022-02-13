package main

import (
	"context"
	"fmt"
	"strconv"

	"github.com/go-redis/redis/v8"
)

var Rdb *redis.Client

var Ctx = context.Background()

func main() {
	Rdb = redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "lifehappy01",
		DB:       0,
	})
	// fmt.Printf("%T %s\n", Rdb.TTL(Ctx, "ckk").Val().String(), Rdb.TTL(Ctx, "ckk").Val().String())
	// Rdb.Set(Ctx, "ck", "lifehappy", redis.KeepTTL)
	// Rdb.Set(Ctx, "ls", "ok", redis.KeepTTL)
	// Rdb.SAdd(Ctx, "student1", "").Result()
	// Rdb.SAdd(Ctx, "student1", "python").Result()
	// courses := Rdb.SMembers(Ctx, "student1").Val()
	// for _, course := range courses {
	// 	fmt.Println(course)
	// }
	// c := make(chan int, 5)
	// go func() {
	// 	for {
	// 		info := <-c
	// 		fmt.Println(info)
	// 	}
	// }()
	// for i := 0; i < 10; i++ {
	// 	c <- i
	// 	fmt.Printf("%d fljljllfs\n", i)
	// }
	fmt.Printf("%T %d\n", Rdb.Decr(Ctx, "sum").Val(), Rdb.Decr(Ctx, "sum").Val())
	val, _ := strconv.Atoi(Rdb.Get(Ctx, "sum").Val())
	fmt.Println(val)
	// fmt.Printf("%T %d\n", val, val)
	// fmt.Println(Rdb.TTL(Ctx, "student1").Val().String())
	// fmt.Println(Rdb.SAdd(Ctx, "student1", "").Result())
	// fmt.Println(Rdb.SMembers(Ctx, "student1").Val())
	// fmt.Printf("%T\n", Rdb.SMembers(Ctx, "studentcourse").Val())
	// fmt.Printf("%T %v\n", Rdb.SIsMember(Ctx, "student1", "python1").Val(), Rdb.SIsMember(Ctx, "student1", "python1").Val())
}
