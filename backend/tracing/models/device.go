package models;

// A device on which kSentinel will run.
type Device struct{
	device_id string
	device_name string
	device_type string  // system/container/pod
}