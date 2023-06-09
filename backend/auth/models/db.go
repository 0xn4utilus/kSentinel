package models

import (
	"database/sql"
	"log"
	"github.com/InfoSecIITR/kSentinel/auth/config"

	_ "github.com/go-sql-driver/mysql"
)

var db *sql.DB

func DB() (db *sql.DB, err error) {
	// dsn := "DB_USER:DB_PASSWORD@tcp(DB_HOST:DB_PORT)/DB_NAME"
	dsn := config.DB_USER + ":"+config.DB_PASSWORD+ "@tcp(" + config.DB_HOST+  ":" + config.DB_PORT + ")/" + config.DB_NAME
	sqlDB, err := sql.Open("mysql", dsn)
	if err != nil {
		log.Println("DB connection failed: ", err)
		return nil, err
	}
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
		err := rows.Scan(&user.Id, &user.Username, &user.Email, &user.Password, &user.ActiveStatus)
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
		err := rows.Scan(&user.Id, &user.Username, &user.Email, &user.Password, &user.ActiveStatus)
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
	stmt, err := db.Prepare("INSERT INTO users (username, email, password) VALUES(?, ?, ? )")
	if err != nil {
		log.Println(err)
	}
	defer stmt.Close()

	if _, err := stmt.Exec(username, email, password); err != nil {
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
