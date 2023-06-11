package models;

// user details
type User struct{
	Id string 
	Username string
	Email string
	Password string
	ActiveStatus bool
}

// device ids of all the devices registered by a user
type UserDevices struct{
	Id string
	Username string
	Device string
}
