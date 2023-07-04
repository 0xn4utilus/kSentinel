package models

import (
	"errors"
	"log"
	"strconv"
	"time"

	"github.com/InfoSecIITR/kSentinel/kscore/globals"
	"gorm.io/gorm"
)

type Event struct {
	DeviceId string `json:"device_id"`
	Type    string `json:"type"`
	Name    string `json:"name"`
	Message string `json:"message"`
	Mode    string `json:"mode"`
}

func (event *Event) CreateEvent() {
	var existingEvent Event
	var device Device
	db := globals.Db
	result := db.Where("device_id = ? AND name = ? AND type = ? AND mode = ?", event.DeviceId,event.Name,event.Type,event.Mode).First(&existingEvent)
	if result.Error != nil && !errors.Is(result.Error, gorm.ErrRecordNotFound) {
		log.Fatal(result.Error)
	}
	if errors.Is(result.Error, gorm.ErrRecordNotFound) {
		log.Println("Creating new event")
		timeStamp := strconv.Itoa(int(time.Now().Unix()))
		db.Create(event)
		db.Model(device).Where("device_id = ?",event.DeviceId).Update("updated_at",timeStamp)
	}
	event.UpdateEvent()
}

func (event* Event) UpdateEvent(){
	db := globals.Db
	timeStamp := strconv.Itoa(int(time.Now().Unix()))
	db.Model(Device{}).Where("device_id = ?",event.DeviceId).Update("updated_at",timeStamp)
	db.Model(event).Where("device_id = ? AND name = ? AND mode = ?",event.DeviceId,event.Name,event.Mode).Update("message",event.Message)
}

func (event* Event)ReadEvents(deviceId string)([]Event){
	db := globals.Db
	var events[] Event
	db.Find(&events,Event{DeviceId:deviceId})
	return events
}