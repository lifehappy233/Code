package main

import (
	"context"
	"fmt"
	"lifehappy/protoLearn/basicdemo/demo"
	"log"
	"net"

	"google.golang.org/grpc"
)

type Server struct {
	demo.UnimplementedSayServer
}

func (s *Server) Hello(ctx context.Context, req *demo.Request) (*demo.Response, error) {
	log.Println(req.Name)
	return &demo.Response{Msg: fmt.Sprintf("Hello, %s\n", req.Name)}, nil
}

func main() {
	conn, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatalln("net.Listen is error: ", err)
	}
	log.Printf("Net is listening: %s\n", conn.Addr().String())

	server := grpc.NewServer()
	demo.RegisterSayServer(server, &Server{})

	if err := server.Serve(conn); err != nil {
		log.Fatalln("server.Server is error: ", err)
	}
}
