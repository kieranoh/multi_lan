package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate надежно хеширует данный сертификат и возвращает хеш в виде шестнадцатичной строки.
// @param cert Сертификат, который нужно хешировать.
// @return Надежно хешированный сертификат в виде шестнадцатичной строки.
func hashCertificate(cert string) string {
	// Создаем новый хеш SHA-256
	hasher := sha256.New()
	
	// Записываем данные сертификата в хеш
	hasher.Write([]byte(cert))
	
	// Получаем хеш в виде байтового среза
	hashBytes := hasher.Sum(nil)
	
	// Преобразуем хеш в шестнадцатеричную строку
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}