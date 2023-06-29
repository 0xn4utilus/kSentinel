package utils

import (
	"math/rand"
	"time"

	"github.com/google/uuid"
)

func GenerateId() string {
	id := uuid.New()
	return id.String()
}

func GenerateRandomString(length int)string{
	chars := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	randStr := ""
	rand.Seed(time.Now().Unix())
	for i:=0;i<length;i++{
		randStr += string(chars[rand.Intn(len(chars))])
	}
	return randStr
}