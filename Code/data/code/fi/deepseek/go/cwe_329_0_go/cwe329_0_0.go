package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Varmistetaan, että avain on vähintään 16 tavua
	if len(key) < 16 {
		// Jos avain on liian lyhyt, täytetään se nollilla
		paddedKey := make([]byte, 16)
		copy(paddedKey, key)
		aesKey = paddedKey
	} else {
		// Käytetään avaimen 16 ensimmäistä tavua AES-avaimena
		aesKey = key[:16]
	}

	// Luodaan AES-salausalgoritmi
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Luodaan satunnainen IV (alkuvektori)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// PKCS7-pakkaus: täytetään data niin, että se on AES-lohkon kerrannainen
	blockSize := block.BlockSize()
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, len(data)+padding)
	copy(padText, data)
	for i := len(data); i < len(padText); i++ {
		padText[i] = byte(padding)
	}

	// Salataan data CBC-tilassa
	encryptedData = make([]byte, len(padText))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, padText)

	return encryptedData, iv, aesKey
}