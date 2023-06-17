package controllers

import (
	"database/sql"
	"encoding/json"
	"log"
	"net/http"

	"github.com/InfoSecIITR/kSentinel/kscore/models"
	"github.com/gofiber/fiber/v2"
)

var Db *sql.DB

func CreateDevice(c *fiber.Ctx) error {
	var message string = "Registration complete";
	statusCode := http.StatusOK
	data := c.Body()
	log.Println(string(data))
	var device models.Device
	err := json.Unmarshal(data, &device)
	if err != nil {
		log.Println(err)
	}
	stmt, err := Db.Prepare("INSERT INTO devices (device_id,device_type,device_kernel) VALUES (?,?,?)")
	defer stmt.Close()
	if err!=nil{
		message = "Internal server error"
		statusCode = http.StatusInternalServerError
		log.Println(err)
	}
	_,err = stmt.Exec(device.DeviceId,device.DeviceType,device.DeviceKernel)
	if err!=nil{
		message = "Internal server error"
		statusCode = http.StatusInternalServerError
		log.Println(err)
	}

	return c.Status(statusCode).SendString(message)
}

func CheckDevice(c *fiber.Ctx) error {
	var message string
	var count int
	statusCode := http.StatusOK
	deviceId := c.Params("deviceid")
	stmt, err := Db.Prepare("SELECT COUNT(*) from devices WHERE device_id = ?")
	defer stmt.Close()
	if err != nil {
		message = "Internal server error"
		log.Println(err)
		statusCode = http.StatusInternalServerError
	}
	err = stmt.QueryRow(deviceId).Scan(&count)
	if err != nil {
		message = "Internal server error"
		statusCode = http.StatusInternalServerError
	}
	if count == 0 {
		message = "Device has not been registered yet"
	} else {
		message = "Device registration has already been completed"
	}
	return c.Status(statusCode).SendString(message)
}
