package main

import (
	"fmt"
	"log"
	"os"

	"github.com/InfoSecIITR/kSentinel/kscore/router"
	"github.com/gofiber/fiber/v2"
	"github.com/joho/godotenv"
	// "github.com/joho/godotenv"
)

func checkEnvVars()bool{
	var error bool
	if os.Getenv("KSCORE_SERVICE_PORT")==""{
		error = true
	}
	return error
}
func main() {
	err := godotenv.Load()
	if err!=nil{
		if checkEnvVars()==true{
			log.Fatal("Error! Cannot read environment variables")
		}
	}
	app := fiber.New()
	router.StartRouter(app)
	port_env := os.Getenv("KSCORE_SERVICE_PORT")
	if port_env==""{
		log.Fatal("Environment variable KSCORE_SERVICE_PORT not found")
	}
	port := fmt.Sprintf(":%s",port_env)
	app.Listen(port)
}