package main

import (
	"lifehappy/camp/router"

	"github.com/gin-gonic/gin"
)

func main() {
	r := gin.Default()
	router.RegisterRouter(r)
	r.Run(":8080")
}
