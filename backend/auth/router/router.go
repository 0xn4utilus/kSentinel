package router

import (
	"github.com/InfoSecIITR/kSentinel/auth/controllers"
	"github.com/gofiber/fiber/v2"
)

func StartRouter(app* fiber.App){
	apiGroup := app.Group("/api")
	authRouter := apiGroup.Group("/auth")
	authRouter.Get("/test",controllers.Test)
	authRouter.Get("/decodecookie/:token",controllers.DecodeCookie)
	authRouter.Get("/validate/:token",controllers.ValidateToken)
	authRouter.Post("/login",controllers.Login)
	authRouter.Post("/register",controllers.Register)
}
