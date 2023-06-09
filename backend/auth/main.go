package main

import (
	"log"
	"github.com/InfoSecIITR/kSentinel/auth/router"
	"github.com/InfoSecIITR/kSentinel/auth/models"
	"github.com/gofiber/fiber/v2"
)

func main() {
	if err := models.InitDB(); err != nil {
		log.Fatal(err)
	}
	app := fiber.New()
	router.StartRouter(app)
	app.Listen(":8080")
}