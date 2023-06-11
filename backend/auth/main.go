package main

import (
	"log"
	"os"
	"github.com/InfoSecIITR/kSentinel/auth/models"
	"github.com/InfoSecIITR/kSentinel/auth/router"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/cors"
	"github.com/joho/godotenv"
)

func main() {
	if err := godotenv.Load();err!=nil{
		log.Fatal(err)
	}
	if err := models.InitDB(); err != nil {
		log.Fatal(err)
	}
	allowedOrigins := os.Getenv("ALLOWED_ORIGINS")
	app := fiber.New()
	app.Use(cors.New(cors.Config{
		AllowOrigins:allowedOrigins,
		AllowHeaders:"Origin, Content-Type, Accept",
	}))
	router.StartRouter(app)
	app.Listen(":8080")
}