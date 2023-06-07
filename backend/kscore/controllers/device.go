package controllers

import (
	"net/http"

	"github.com/gofiber/fiber/v2"
)

func CreateDevice(c *fiber.Ctx)error{
	return c.Status(http.StatusOK).SendString("Created a new device");
}