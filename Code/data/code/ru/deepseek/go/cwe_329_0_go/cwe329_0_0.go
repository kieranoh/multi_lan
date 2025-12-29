package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Определяем необходимую длину ключа AES (16, 24 или 32 байта для AES-128, AES-192, AES-256 соответственно)
	// Используем AES-256 для максимальной безопасности, если ключ достаточно длинный
	keyLength := 32 // AES-256

	// Проверяем, что ключ достаточно длинный
	if len(key) < keyLength {
		// Если ключ короче необходимого, паникуем (или можно вернуть ошибку, но сигнатура не позволяет)
		panic("key is too short")
	}

	// Берем префикс ключа нужной длины
	aesKey = key[:keyLength]

	// Создаем новый шифр AES с полученным ключом
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Создаем IV (вектор инициализации) длиной, равной размеру блока AES
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Создаем шифратор CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Данные должны быть кратны размеру блока AES
	// Добавляем padding (PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Шифруем данные
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}