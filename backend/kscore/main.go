package main

import (
	"fmt"
	"log"
	"os"
	"github.com/InfoSecIITR/kSentinel/kscore/database"
	"github.com/InfoSecIITR/kSentinel/kscore/globals"
	"github.com/InfoSecIITR/kSentinel/kscore/router"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/cors"
	"github.com/joho/godotenv"
	// "github.com/joho/godotenv"
)

func checkEnvVars()bool{
	var err bool
	if os.Getenv("KSCORE_SERVICE_PORT")==""{
		err = true
	}
	return err
}
func main() {
	err := godotenv.Load()
	if err!=nil{
		if checkEnvVars()==true{
			log.Fatal("Error! Cannot read environment variables")
		}
	}
	
	db := database.InitDb()
	globals.Db = db
	allowedOrigins := os.Getenv("ALLOWED_ORIGINS")
	app := fiber.New()
	app.Use(cors.New(cors.Config{
		AllowOrigins:allowedOrigins,
		AllowHeaders:"Origin, Content-Type, Accept",
	}))
	router.StartRouter(app)
	port_env := os.Getenv("KSCORE_SERVICE_PORT")
	if port_env==""{
		log.Fatal("Environment variable KSCORE_SERVICE_PORT not found")
	}
	port := fmt.Sprintf(":%s",port_env)
	err = app.Listen(port)
	if err!=nil{
		panic(err)
	}
}