package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData шифрует данные с помощью предоставленного ключа, используя AES и режим CBC.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes")
	}

	// Используем только первые 16 байт ключа для AES-128.
	aesKey = key[:16]

	// Генерируем вектор инициализации (IV) длиной 16 байт.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Создаем новый блок шифратор.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Выравниваем данные по размеру блока AES.
	paddedData := pad(data, aes.BlockSize)

	// Создаем новую шифровальную оболочку с использованием режима CBC.
	mode := cipher.NewCBCEncrypter(block, iv)

	// Шифруем данные.
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad добавляет паддинг к данным в соответствии с PKCS#7.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}