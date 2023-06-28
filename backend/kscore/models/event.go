package models

import (
	"errors"
	"log"

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
	db := globals.Db
	result := db.Where("device_id = ? AND name = ? AND type = ? AND mode = ?", event.DeviceId,event.Name,event.Type,event.Mode).First(&existingEvent)
	if result.Error != nil && !errors.Is(result.Error, gorm.ErrRecordNotFound) {
		log.Fatal(result.Error)
	}
	if errors.Is(result.Error, gorm.ErrRecordNotFound) {
		log.Println("Creating new event")
		db.Create(event)
	}
	event.UpdateEvent()
}

func (event* Event) UpdateEvent(){
	db := globals.Db
	db.Model(event).Where("device_id = ? AND name = ? AND mode = ?",event.DeviceId,event.Name,event.Mode).Update("message",event.Message)
}
