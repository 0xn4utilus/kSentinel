package database

import (
	"database/sql"
	"fmt"
	"log"
	_ "github.com/go-sql-driver/mysql"
	"os"
)

func InitDb() (db *sql.DB) {
	// dsn := "DB_USER:DB_PASSWORD@tcp(DB_HOST:DB_PORT)/DB_NAME"
	log.Println("Initializing kscore database..")
	dbUser := os.Getenv("DB_USER")
	dbPassword := os.Getenv("DB_PASSWORD")
	dbHost := os.Getenv("DB_HOST")
	dbPort := os.Getenv("DB_PORT")
	dbName := os.Getenv("DB_NAME")
	dsn := fmt.Sprintf("%s:%s@tcp(%s:%s)/%s", dbUser, dbPassword, dbHost, dbPort, dbName)
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		panic(err)
	}
	stmt, err := db.Prepare("CREATE TABLE IF NOT EXISTS devices (device_id VARCHAR(255) UNIQUE,device_type VARCHAR(255),device_kernel VARCHAR(255));")
	if err != nil {
		panic(err)
	}
	_, err = stmt.Exec()
	if err != nil {
		panic(err)
	}
	return db
}
