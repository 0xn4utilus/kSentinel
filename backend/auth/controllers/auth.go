package controllers

import (
	"net/http"

	"github.com/gofiber/fiber/v2"
)

func Register(c* fiber.Ctx)error{
	return c.Status(http.StatusOK).SendString("Registration successful")
}

func Login(c* fiber.Ctx)error{
	return c.Status(http.StatusOK).SendString("Login successful")
}