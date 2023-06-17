package main

import (
	"fmt"
	"log"
	"os"

	"github.com/InfoSecIITR/kSentinel/kscore/controllers"
	"github.com/InfoSecIITR/kSentinel/kscore/database"
	"github.com/InfoSecIITR/kSentinel/kscore/router"
	"github.com/gofiber/fiber/v2"
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
	controllers.Db = db
	app := fiber.New()
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