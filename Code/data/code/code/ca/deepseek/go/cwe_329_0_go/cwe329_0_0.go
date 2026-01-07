package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Utilitzem els primers 32 bytes de la clau per a AES-256
	const keyLength = 32
	if len(key) < keyLength {
		// Això no hauria de passar segons la descripció, però ho comprovem per seguretat
		panic("key length insufficient")
	}
	aesKey = key[:keyLength]

	// Creem el bloc AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Creem l'IV (16 bytes per a AES)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Preparem les dades per a xifrar (PKCS#7 padding)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Xifrem les dades
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}