package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the provided data using either AES or DES algorithm in CBC mode.
// The provided key bytes are sufficient length for both AES and DES (>= 64 bytes).
// Only one algorithm is chosen, and the prefix of the key bytes is used according to the required length.
// The function returns the encrypted data, the initialization vector (IV), and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Check if the key length is valid for AES (16, 24, or 32 bytes)
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long for AES")
	}

	// Use the first 16 bytes of the key for AES encryption
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV for CBC mode
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	data = pad(data, aes.BlockSize)

	// Create a CBC encrypter
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData := make([]byte, len(data))
	cbc.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad adds padding to the data to ensure it is a multiple of the block size.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}