package main

import (
	"github.com/gofiber/fiber/v2"
	"github.com/InfoSecIITR/kSentinel/tracing/router"
)

func main() {
	app := fiber.New()
	router.StartRouter(app)
}