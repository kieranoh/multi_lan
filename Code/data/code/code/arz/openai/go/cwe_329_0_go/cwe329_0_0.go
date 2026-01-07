package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// The provided key bytes must be long enough (>= 16 bytes). 
// Use the prefix of the provided key bytes to match the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is at least 16 bytes long
	if len(key) < 16 {
		panic("Key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Generate a new IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	cbc := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Encrypt the data
	encryptedData = make([]byte, len(padtext))
	cbc.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey
}