package router

import (
	"github.com/InfoSecIITR/kSentinel/kscore/controllers"
	"github.com/gofiber/fiber/v2"
)

func StartRouter(app *fiber.App) {
	apiGroup := app.Group("/api")
	route := apiGroup.Group("/kscore")

	route.Get("/checkdevice/:deviceid",controllers.CheckDevice)
	route.Get("/key/:deviceid",controllers.FetchKey)
	route.Get("/events/:deviceid",controllers.FetchEvents)
	route.Get("/events/lastupdate/:deviceid",controllers.FetchLastUpdate)
	route.Post("/device",controllers.CreateDevice)
	route.Post("/events/:deviceid",controllers.CreateEvent)
}