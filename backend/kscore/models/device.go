package models;

// A device on which kSentinel will run.
type Device struct{
	device_id string
	device_type string  // system/container/pod
	device_kernel string // kernel version
}