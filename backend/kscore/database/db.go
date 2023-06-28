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


// func InitDb() (db *sql.DB) {
// 	// dsn := "DB_USER:DB_PASSWORD@tcp(DB_HOST:DB_PORT)/DB_NAME"
	// log.Println("Initializing kscore database..")
	// dbUser := os.Getenv("DB_USER")
	// dbPassword := os.Getenv("DB_PASSWORD")
	// dbHost := os.Getenv("DB_HOST")
	// dbPort := os.Getenv("DB_PORT")
	// dbName := os.Getenv("DB_NAME")
	// dsn := fmt.Sprintf("postgresql://%s:%s@%s:%s/%s?sslmode=disable", dbUser, dbPassword, dbHost, dbPort, dbName)
	// db, err := sql.Open("postgres", dsn)
// 	if err != nil {
// 		panic(err)
// 	}
// 	stmt, err := db.Prepare("CREATE TABLE IF NOT EXISTS devices (device_id VARCHAR(255) UNIQUE,device_type VARCHAR(255),device_kernel VARCHAR(255));")
// 	if err != nil {
// 		panic(err)
// 	}
// 	_, err = stmt.Exec()
// 	if err != nil {
// 		panic(err)
// 	}
// 	stmt,err = db.Prepare("CREATE TABLE IF NOT EXISTS events (device_ID VARCHAR(255) PRIMARY KEY,data jsonb[]);")
// 	if err!=nil{
// 		panic(err)
// 	}
// 	_,err = stmt.Exec()
// 	if err!=nil{
// 		panic(err)
// 	}
// 	return db
// }

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
	db.AutoMigrate(&models.Device{})
	db.AutoMigrate(&models.Event{})
	globals.Db = db
	return db
}
