package controllers

import "github.com/gofiber/fiber/v2"

func CreateEvent(c* fiber.Ctx)error{
	return c.SendString("")
}