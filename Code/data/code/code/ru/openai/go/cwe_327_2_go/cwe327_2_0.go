package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData шифрует данные с помощью ключа, используя режим CBC.
// Возвращает зашифрованные данные, IV и ключ, использованный для шифрования.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Проверка длины ключа для AES (должен быть 16, 24 или 32 байта)
	if len(key) < 16 {
		return nil, nil, nil, errors.New("ключ должен быть не менее 16 байт для AES")
	}
	
	// Используем первые 32 байта ключа для AES
	aesKey := key[:32]

	// Создание нового блока шифрования
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Генерация вектора инициализации (IV)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Подготовка данных для шифрования
	paddedData := pad(data, aes.BlockSize)

	// Создание шифратора в режиме CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Шифрование данных
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad добавляет padding к данным для соответствия размеру блока
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}