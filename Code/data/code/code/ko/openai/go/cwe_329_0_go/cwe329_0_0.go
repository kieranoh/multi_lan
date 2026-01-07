package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData encrypts data using AES in CBC mode.
// The provided key bytes are sufficient (>= 16 bytes).
// Use the prefix of the provided key bytes to match the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key length is suitable for AES
	if len(key) < 16 {
		panic("key length must be at least 16 bytes")
	}

	// Use the first 16 bytes of the key for AES
	aesKey = key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Create a new IV for the CBC mode
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad the data to be a multiple of the block size
	pad := aes.BlockSize - len(data)%aes.BlockSize
	padding := bytes.Repeat([]byte{byte(pad)}, pad)
	data = append(data, padding...)

	// Encrypt the data in CBC mode
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey
}