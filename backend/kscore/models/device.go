package models;

// A device on which kSentinel will run.
type Device struct{
	DeviceId string `json:"device_id"`
	DeviceType string  `json:"device_type"`// system/container/pod
	DeviceKernel string `json:"device_kernel"`// kernel version
}