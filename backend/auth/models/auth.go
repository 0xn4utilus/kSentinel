package models;

type User struct{
	name string
	password string
	email string
	accountActive bool
	id string
	user_devices []string // device_ids of all the devices registered by a user
}