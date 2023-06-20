package controllers

import (
	"fmt"
	"log"
	"os"

	"github.com/golang-jwt/jwt/v4"
	"golang.org/x/crypto/bcrypt"
)

func HashPassword(password string) string {
	passwordByte := []byte(password)
	hash, err := bcrypt.GenerateFromPassword(passwordByte, bcrypt.DefaultCost)
	if err != nil {
		log.Println(err)
	}
	return string(hash)
}

func ComparePassword(hashPassword string, password string) error {
	passwordByte := []byte(password)
	hash := []byte(hashPassword)
	err := bcrypt.CompareHashAndPassword(hash, passwordByte)
	return err
}

func DecodeToken(token string)(string,bool){
	secret := []byte(os.Getenv("JWT_SECRET"))
	tok,err := jwt.Parse(token,func(tok *jwt.Token)(interface{},error){
		if _,ok := tok.Method.(*jwt.SigningMethodHMAC); !ok{
			return nil,fmt.Errorf("Unexpected signing method: %v",tok.Header["alg"])
		}
		return secret,nil
	})
	if err!=nil{
		return err.Error(),false
	}
	if tok.Valid{
		claims := tok.Claims.(jwt.MapClaims)
		username := claims["username"].(string)
		return username,true
	}
	return "Invalid token",false
}