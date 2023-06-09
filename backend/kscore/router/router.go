package router

import (
	"github.com/gofiber/fiber/v2"
	"github.com/InfoSecIITR/kSentinel/kscore/controllers"
)

func StartRouter(app *fiber.App) {
	apiGroup := app.Group("/api")
	route := apiGroup.Group("/tracing")
	route.Post("/device",controllers.CreateDevice)
}