package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Usar los primeros 32 bytes de la clave proporcionada para AES-256
	keyLength := 32
	if len(key) < keyLength {
		keyLength = len(key)
	}
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])

	// Crear el cifrador de bloque AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Crear el IV (vector de inicialización)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Añadir relleno PKCS#7 a los datos
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Cifrar los datos en modo CBC
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}