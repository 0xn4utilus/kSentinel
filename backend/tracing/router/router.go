package router

import (
	"github.com/gofiber/fiber/v2"
	"github.com/InfoSecIITR/kSentinel/tracing/controllers"
)

func StartRouter(app *fiber.App) {
	route := app.Group("/api")
	route.Post("/create_device",controllers.CreateDevice)
}