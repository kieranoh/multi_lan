package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"fmt"
	"io"
)

// encryptData encrypts the provided data using AES in CBC mode with the given key.
// The provided key bytes must be at least 16 bytes long. The prefix of the provided
// key bytes is used to meet the necessary length.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure key is at least 16 bytes
	if len(key) < 16 {
		panic("Key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES
	aesKey = key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Generate a new IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad the data to be a multiple of block size
	paddedData := pad(data, aes.BlockSize)

	// Create a new CBC encrypter and encrypt the data
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pad adds PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padded := make([]byte, len(data)+padding)
	copy(padded, data)
	for i := len(data); i < len(padded); i++ {
		padded[i] = byte(padding)
	}
	return padded
}