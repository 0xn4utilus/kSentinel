package controllers

import (
	"net/http"

	"github.com/gofiber/fiber/v2"
)

func Test(c* fiber.Ctx)error{
	return c.Status(http.StatusOK).SendString("Auth service is up and running");
}