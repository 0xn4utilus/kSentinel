package router

import (
	"github.com/InfoSecIITR/kSentinel/auth/controllers"
	"github.com/gofiber/fiber/v2"
)

func StartRouter(app* fiber.App){
	apiGroup := app.Group("/api")
	route := apiGroup.Group("/auth")

	route.Get("/test",controllers.Test)

	route.Post("/login",controllers.Login)
	route.Post("/register",controllers.Register)
}
