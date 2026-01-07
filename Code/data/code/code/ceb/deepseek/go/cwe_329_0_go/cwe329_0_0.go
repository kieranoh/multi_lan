package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key bytes.
// The provided key bytes must be sufficiently long (>= 64 bytes). The prefix of
// the provided key bytes is used to fit the required length.
// Returns the encrypted data, IV, and the AES key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is at least 64 bytes long
	if len(key) < 64 {
		// If key is too short, pad with zeros (or handle error as per your requirements)
		paddedKey := make([]byte, 64)
		copy(paddedKey, key)
		key = paddedKey
	}

	// Use the first 32 bytes of the key for AES-256
	aesKey = key[:32]

	// Create a new AES cipher with the derived key
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// In production, handle error appropriately
		panic(err)
	}

	// Generate a random IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad the data to be a multiple of the block size
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Create the CBC mode encrypter
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pkcs7Pad pads data to the specified block size using PKCS#7 padding.
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}

// Note: In a real implementation, consider returning errors instead of panicking.
// The function signature would then be:
// func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error)