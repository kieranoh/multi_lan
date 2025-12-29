package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"io"
)

// encryptData encrypts the given data using the provided key in CBC mode
// and returns the encrypted data, IV, and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Ensure the key is at least 32 bytes for AES-256
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
	}

	// Use the first 32 bytes of the key for AES-256
	aesKey := key[:32]

	// Create a new AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV (Initialization Vector)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	data = pad(data, aes.BlockSize)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad adds PKCS#7 padding to the data
func pad(src []byte, blockSize int) []byte {
	padding := blockSize - len(src)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(src, padtext...)
}