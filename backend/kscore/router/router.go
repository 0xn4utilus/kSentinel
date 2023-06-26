package router

import (
	"github.com/InfoSecIITR/kSentinel/kscore/controllers"
	"github.com/gofiber/fiber/v2"
)

func StartRouter(app *fiber.App) {
	apiGroup := app.Group("/api")
	route := apiGroup.Group("/kscore")
	route.Post("/device",controllers.CreateDevice)
	route.Get("/checkdevice/:deviceid",controllers.CheckDevice)
	route.Post("/events/:deviceid",controllers.CreateEvent)
}