package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData encrypts the provided data using AES and CBC mode with the given key.
// The provided key bytes are assumed to be long enough (>= 16 bytes).
// Use the prefix of the provided key bytes that fits the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is 16, 24, or 32 bytes long (for AES-128, AES-192, or AES-256)
	var aesKeyLength int
	switch len(key) {
	case 16, 24, 32:
		aesKeyLength = len(key)
	default:
		aesKeyLength = 16 // Default to AES-128 if key is not of valid length
	}

	// Use only the prefix of the key that fits the required length
	aesKey = key[:aesKeyLength]

	// Generate a new IV (initialization vector) for CBC mode
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err) // Handle error appropriately in production code
	}

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err) // Handle error appropriately in production code
	}

	// Pad the data to be a multiple of the block size
	data = pad(data, block.BlockSize())

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey
}

// pad adds PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}