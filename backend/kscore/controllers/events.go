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

func FetchEvents(c* fiber.Ctx)error{
	status := http.StatusOK
	message := "Failed to fetch events"
	var event models.Event
	deviceId := c.Params("deviceid")
	events := event.ReadEvents(deviceId)
	data,err := json.Marshal(events)
	if err!=nil{
		log.Println(err)
		message = err.Error()
	}else{
		message = string(data)
	}
	return c.Status(status).SendString(message)
}