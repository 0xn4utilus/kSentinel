package models

import "github.com/InfoSecIITR/kSentinel/kscore/globals"

// A device on which kSentinel will run.
type Device struct{
	DeviceId string `json:"device_id" gorm:"primaryKey"`
	DeviceType string  `json:"device_type"`// system/container/pod
	DeviceKernel string `json:"device_kernel"`// kernel version
	DeviceKey string `json:"device_key"` // 256-bit AES key
}

// Use * for fetching all items
func (device* Device)FetchItem(key,deviceId string)(string,bool){
	var message string
	db := globals.Db
	status := true
	
	var result Device
	tx := db.Table("devices").Where("device_id = ?",deviceId).Select(key).Scan(&result)
	if tx.Error!=nil{
		status = false
		message = tx.Error.Error()
	}else{
		message = result.DeviceKey
	}
	return message,status
}