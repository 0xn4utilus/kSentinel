package controllers

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/InfoSecIITR/kSentinel/kscore/models"
	"github.com/gofiber/fiber/v2"
)

func CreateEvent(c *fiber.Ctx) error {
	var events []models.Event
	status := http.StatusOK
	message := "Created event"
	deviceId := c.Params("deviceid")
	err := json.Unmarshal(c.Body(), &events)
	if err != nil {
		message = err.Error()
		status = http.StatusBadRequest
		log.Println(message)
	} else {
		for _,event := range events{
			event.DeviceId = deviceId
			event.CreateEvent()
		}
	}

	return c.Status(status).SendString(message)
}
