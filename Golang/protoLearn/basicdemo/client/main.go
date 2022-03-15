package main

import (
	"context"
	"fmt"
	"lifehappy/protoLearn/basicdemo/demo"
	"log"

	"google.golang.org/grpc"
)

func main() {
	conn, err := grpc.Dial("127.0.0.1:8080", grpc.WithInsecure())
	if err != nil {
		log.Fatalln("grpc.Dail is error: ", err)
	}
	client := demo.NewSayClient(conn)

	var msg string = "lifehappy"
	response, err := client.Hello(context.Background(), &demo.Request{Name: msg})
	if err != nil {
		log.Fatalln("client.Hello is error: ", err)
	}
	fmt.Printf("%s", response.Msg)
}
