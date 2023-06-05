package main

import (
	"github.com/InfoSecIITR/kSentinel/auth/router"
	"github.com/gofiber/fiber/v2"
)

func main() {
	app := fiber.New()
	router.StartRouter(app)
	app.Listen(":8080")
}