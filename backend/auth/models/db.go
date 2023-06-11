package models

import (
	"database/sql"
	"log"
	"os"

	"github.com/InfoSecIITR/kSentinel/utils"
	_ "github.com/go-sql-driver/mysql"
)

var db *sql.DB

func DB() (db *sql.DB, err error) {
	dbUser := os.Getenv("DB_USER")
	dbPassword := os.Getenv("DB_PASSWORD")
	dbHost := os.Getenv("DB_HOST")
	dbPort := os.Getenv("DB_PORT")
	dbName := os.Getenv("DB_NAME")

	// dsn := "DB_USER:DB_PASSWORD@tcp(DB_HOST:DB_PORT)/DB_NAME"
	dsn := dbUser + ":"+dbPassword+ "@tcp(" + dbHost+  ":" + dbPort + ")/" + dbName
	sqlDB, err := sql.Open("mysql", dsn)
	if err != nil {
		log.Println("DB connection failed: ", err)
		return nil, err
	}
	stmt,err := sqlDB.Prepare("CREATE TABLE IF NOT EXISTS users (username VARCHAR(20) NOT NULL UNIQUE,email VARCHAR(255) NOT NULL UNIQUE,password VARCHAR(255), activestatus BOOLEAN DEFAULT false, id VARCHAR(72))")
	if err!=nil{
		log.Fatal(err)
	}
	if _,err := stmt.Exec();err!=nil{
		log.Fatal(err)
	}
	defer stmt.Close()
	return sqlDB, nil
}

func InitDB() (err error) {
	if db, err = DB(); err != nil {
		return err
	}
	return nil
}

func GetUserInfoByUsername(username string) (User, error) {
	stmt, err := db.Prepare("SELECT * FROM users where username = ?")
	if err != nil {
		log.Println(err)
	}
	defer stmt.Close()
	var user User
	rows, err := stmt.Query(username)
	if err != nil {
		log.Println(err)
	}
	defer rows.Close()

	for rows.Next() {
		err := rows.Scan( &user.Username, &user.Email, &user.Password, &user.ActiveStatus,&user.Id)
		if err != nil {
			log.Println(err)
		}
	}
	if err = rows.Err(); err != nil {
		log.Println(err)
	}
	return user, nil
}

func GetUserInfoByEmail(email string) (User, error) {
	stmt, err := db.Prepare("SELECT * FROM users where email = ?")

	if err != nil {
		log.Println(err)
	}
	defer stmt.Close()
	var user User
	rows, err := stmt.Query(email)
	if err != nil {
		log.Println(err)
	}
	defer rows.Close()

	for rows.Next() {
		err := rows.Scan( &user.Username, &user.Email, &user.Password, &user.ActiveStatus,&user.Id)
		if err != nil {
			log.Println(err)
		}
	}
	if err = rows.Err(); err != nil {
		log.Println(err)
	}
	return user, nil
}

func InsertNewUser(username string, email string, password string) (err error) {
	userId := utils.GenerateId()
	stmt, err := db.Prepare("INSERT INTO users (username, email, password, id) VALUES(?, ?, ?, ?)")
	if err != nil {
		log.Println(err)
	}
	defer stmt.Close()

	if _, err := stmt.Exec(username, email, password,userId); err != nil {
		log.Println(err)
		return err
	}
	return nil
}

func ActivateUser(username string) (err error) {
	stmt, err := db.Prepare("update users set activeStatus=1 where username = ?")
	if err != nil {
		log.Println(err)
	}
	defer stmt.Close()

	if _, err := stmt.Exec(username); err != nil {
		log.Println(err)
		return err
	}
	return nil
}
