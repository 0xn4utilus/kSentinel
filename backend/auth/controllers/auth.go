package controllers

import (
	"fmt"
	"log"
	"net/http"
	"os"
	"time"
	"github.com/InfoSecIITR/kSentinel/auth/models"
	"github.com/gofiber/fiber/v2"
	"github.com/golang-jwt/jwt/v4"
	"golang.org/x/crypto/bcrypt"
)



type UserParser struct {
	Username string `json:"username"`
	Email    string `json:"email"`
	Password string `json:"password"`
}

type JWTClaims struct {
	Username string `json:"username"`
	jwt.RegisteredClaims
}

func HashPassword(password string) string {
	passwordByte := []byte(password)
	hash, err := bcrypt.GenerateFromPassword(passwordByte, bcrypt.DefaultCost)
	if err != nil {
		fmt.Println(err)
	}
	return string(hash)
}

func ComparePassword(hashPassword string, password string) error {
	passwordByte := []byte(password)
	hash := []byte(hashPassword)
	err := bcrypt.CompareHashAndPassword(hash, passwordByte)
	return err
}

func Register(c *fiber.Ctx) error {
	userParser := new(UserParser)
	if err := c.BodyParser(userParser); err != nil {
		log.Println(err)
	}
	if userParser.Username == "" || userParser.Email == "" || userParser.Password == "" {
		return c.Status(http.StatusBadRequest).SendString("All fields are required")
	}
	if len(userParser.Username) > 20 || len(userParser.Email) > 255 || len(userParser.Password) > 255 {
		return c.Status(http.StatusBadRequest).SendString("Maximum length of fields exceeded")
	}

	if user, err := models.GetUserInfoByUsername(userParser.Username); err == nil {
		if user.Username != "" {
			return c.Status(http.StatusBadRequest).SendString("Username already taken")
		}
	}
	if user, err := models.GetUserInfoByEmail(userParser.Email); err == nil {
		if user.Email != "" {
			return c.Status(http.StatusBadRequest).SendString("Email already taken")
		}
	}
	if err := models.InsertNewUser(userParser.Username, userParser.Email, HashPassword(userParser.Password)); err != nil {
		return c.Status(http.StatusBadRequest).SendString("Registration failed")
	}

	return c.Status(http.StatusOK).SendString("Registration successful")
}

func Login(c *fiber.Ctx) error {
	userParser := new(UserParser)
	if err := c.BodyParser(userParser); err != nil {
		log.Println(err)
	}

	if userParser.Username == "" || userParser.Password == "" {
		return c.Status(http.StatusBadRequest).SendString("All fields are required")
	}

	if len(userParser.Username) > 72 || len(userParser.Password) > 72 {
		return c.Status(http.StatusBadRequest).SendString("Maximum length of fields exceeded")
	}

	if userParser.Username != "" {
		userDetails, _ := models.GetUserInfoByUsername(userParser.Username)
		if userDetails.Username == "" {
			return c.Status(http.StatusBadRequest).SendString("Username not found")
		}
		if err := ComparePassword(userDetails.Password, userParser.Password); err == nil {
			expirationTime := time.Now().Add(7 * 24 * time.Hour)
			claims := &JWTClaims{
				Username: userDetails.Username,
				RegisteredClaims: jwt.RegisteredClaims{
					ExpiresAt: jwt.NewNumericDate(expirationTime),
				},
			}
			token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
			// Create the JWT string
			jwtKey  := []byte(os.Getenv("JWT_SECRET"))
			tokenString, err := token.SignedString(jwtKey)
			if err != nil {
				log.Println(err)
				return c.Status(http.StatusInternalServerError).SendString("Login Failed")
			}
			// Set Cookie
			cookie := new(fiber.Cookie)
			cookie.Name = "token"
			cookie.Value = tokenString
			cookie.Expires = expirationTime

			c.Cookie(cookie)
			return c.Status(http.StatusOK).SendString("Login successful")
		}

	}

	return c.Status(http.StatusUnauthorized).SendString("Login Failed")
}
