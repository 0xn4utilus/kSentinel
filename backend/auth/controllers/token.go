package controllers

import (
	"net/http"

	"github.com/gofiber/fiber/v2"
)

func ValidateToken(c* fiber.Ctx)error{
	token := c.Params("token")
	value,success := DecodeToken(token)
	if !success{
		return c.Status(http.StatusBadRequest).SendString(value)
	}
	return c.Status(http.StatusOK).SendString("Valid")
}

func DecodeCookie(c* fiber.Ctx)error{
	token := c.Params("token")
	data,success := DecodeToken(token)
	if !success{
		return c.Status(http.StatusBadRequest).SendString(data)
	}
	return c.Status(http.StatusOK).SendString(data)
}