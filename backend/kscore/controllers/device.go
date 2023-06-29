package controllers

import (
	// "database/sql"
	// "encoding/json"
	"encoding/json"
	"errors"
	"io/ioutil"
	"log"
	"net/http"
	"os"

	"github.com/InfoSecIITR/kSentinel/kscore/globals"
	"github.com/InfoSecIITR/kSentinel/kscore/models"
	"github.com/InfoSecIITR/kSentinel/utils"
	"github.com/gofiber/fiber/v2"
	"gorm.io/gorm"
)

func CreateDevice(c *fiber.Ctx) error {
	log.Println("Received registration request")
	var message string = "Registration complete"
	statusCode := http.StatusOK
	data := c.Body()
	var device models.Device
	err := json.Unmarshal(data, &device)
	if err != nil {
		log.Println(err)
	}
	device.DeviceKey = utils.GenerateRandomString(32) // 256 bit key for AES
	db := globals.Db
	tx := db.Create(device)
	if tx.Error != nil {
		message = tx.Error.Error()
		statusCode = http.StatusInternalServerError
		log.Println(tx.Error.Error())
	}
	return c.Status(statusCode).SendString(message)
}

func CheckDevice(c *fiber.Ctx) error {
	var message string
	var device models.Device
	statusCode := http.StatusOK
	db := globals.Db
	deviceId := c.Params("deviceid")
	result := db.Where("device_id = ?", deviceId).First(&device)
	if result.Error != nil {
		if errors.Is(result.Error, gorm.ErrRecordNotFound) {
			message = "Device has not been registered yet"
		} else {
			message = "Internal server error"
			statusCode = http.StatusInternalServerError
		}
	} else {
		message = "Device registration has already been completed"
	}
	return c.Status(statusCode).SendString(message)
}

func FetchKey(c *fiber.Ctx) error {
	var device *models.Device
	statusCode := http.StatusOK
	var message string

	deviceId := c.Params("deviceid")
	token := c.Query("token")
	authApi := os.Getenv("KS_AUTH_API")
	tokenCheckUrl := authApi + "/api/auth/validate/" + token
	resp, err := http.Get(tokenCheckUrl)
	if err != nil {
		message = err.Error()
		statusCode = http.StatusInternalServerError
	} else {
		data,_ := ioutil.ReadAll(resp.Body)
		if string(data) != "Valid" {
			message = string(data)
			statusCode = http.StatusUnauthorized
		} else {
			data, success := device.FetchItem("device_key", deviceId)
			message = data
			if success == false {
				statusCode = http.StatusNotFound
			}
		}
	}

	return c.Status(statusCode).SendString(message)
}
