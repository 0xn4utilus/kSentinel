package database

import (
	"fmt"
	"log"
	"os"

	"github.com/InfoSecIITR/kSentinel/kscore/models"
	"github.com/InfoSecIITR/kSentinel/kscore/globals"
	_ "github.com/lib/pq"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
)


func InitDb()*gorm.DB{
	log.Println("Initializing kscore database..")
	dbUser := os.Getenv("DB_USER")
	dbPassword := os.Getenv("DB_PASSWORD")
	dbHost := os.Getenv("DB_HOST")
	dbPort := os.Getenv("DB_PORT")
	dbName := os.Getenv("DB_NAME")
	dsn := fmt.Sprintf("postgresql://%s:%s@%s:%s/%s", dbUser, dbPassword, dbHost, dbPort, dbName)
	db,err := gorm.Open(postgres.Open(dsn),&gorm.Config{})
	if err!=nil{
		log.Fatal(err)
	}
	db.Exec("CREATE TABLE IF NOT EXISTS devices(device_id text UNIQUE NOT NULL,device_type text NOT NULL,device_kernel text NOT NULL,device_key text NOT NULL, updated_at text NOT NULL);")
	db.AutoMigrate(&models.Event{})
	globals.Db = db
	return db
}
