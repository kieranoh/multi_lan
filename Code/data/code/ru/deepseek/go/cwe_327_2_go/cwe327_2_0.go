package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Проверяем входные данные
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// Выбираем AES-256 (требует 32 байта ключа)
	const aesKeyLength = 32
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// Создаем блок шифрования AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Генерируем IV (вектор инициализации)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Создаем шифратор CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Дополняем данные до размера блока AES
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	// Добавляем PKCS#7 padding
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Шифруем данные
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}