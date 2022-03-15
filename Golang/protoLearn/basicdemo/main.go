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
	log.Printf("%s\n", req.Name)
	return &demo.Response{Msg: fmt.Sprintf("Hello, %s\n", req.Name)}, nil
}

func main() {
	lis, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Fatalln("net.Listen is err: ", err)
	}
	server := grpc.NewServer()

	demo.RegisterSayServer(server, &Server{})
	log.Printf("Listing Address: %s\n", lis.Addr().String())

	if err := server.Serve(lis); err != nil {
		log.Fatalln("server.Server is err: ", err)
	}
}
