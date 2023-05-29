package models;

type User struct{
	user_name string
	user_id string
	user_email string
	user_devices []string // device_ids of all the devices registered by a user
}