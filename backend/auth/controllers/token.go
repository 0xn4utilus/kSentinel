package controllers

import (
	"fmt"
	"net/http"
	"os"

	"github.com/gofiber/fiber/v2"
	"github.com/golang-jwt/jwt/v4"
)

func ValidateToken(c* fiber.Ctx)error{
	tokenStr := c.Params("token")
	secret := []byte(os.Getenv("JWT_SECRET"))
	token,err := jwt.Parse(tokenStr,func(tok *jwt.Token)(interface{},error){
		if _,ok := tok.Method.(*jwt.SigningMethodHMAC); !ok{
			return nil,fmt.Errorf("Unexpected signing method: %v",tok.Header["alg"])
		}
		return secret,nil
	})
	if err!=nil{
		return c.Status(http.StatusForbidden).SendString(err.Error())
	}
	if _, ok := token.Claims.(jwt.MapClaims); ok && token.Valid {
        return c.Status(http.StatusOK).SendString("Valid")
    }
	return c.Status(http.StatusInternalServerError).SendString("Internal server error")
}