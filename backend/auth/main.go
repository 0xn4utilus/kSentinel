package main

import (
	"fmt"
	"log"
	"os"

	"github.com/InfoSecIITR/kSentinel/auth/models"
	"github.com/InfoSecIITR/kSentinel/auth/router"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/cors"
	"github.com/joho/godotenv"
)

func load_env_vars()bool{
	var error bool
	if os.Getenv("ALLOWED_ORIGINS")==""{
		fmt.Println("ALLOWED_ORIGINS not found")
		error = true
	}
	if os.Getenv("DB_USER")==""{
		fmt.Println("DB_USER not found")
		error = true
	}
	if os.Getenv("DB_PASSWORD")==""{
		fmt.Println("DB_PASSWORD not found")
		error = true
	}
	if os.Getenv("DB_HOST")==""{
		fmt.Println("DB_HOST not found")
		error = true
	}
	if os.Getenv("JWT_SECRET")==""{
		fmt.Println("JWT_SECRET not found")
		error = true
	}
	if os.Getenv("DB_NAME")==""{
		fmt.Println("DB_NAME not found")
		error = true
	}
	if os.Getenv("DB_PORT")==""{
		fmt.Println("DB_PORT not found")
		error = true
	}
	return error
}
func main() {
	if err := godotenv.Load();err!=nil{
		if load_env_vars()==true{
			log.Fatal("All environment variables not found")
		}
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