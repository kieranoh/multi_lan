package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode with the provided key.
// It returns the encrypted data, IV (initialization vector), and the AES key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Ensure the key is at least 16 bytes for AES
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes for AES")
	}

	// Use the first 16 bytes of the key for AES
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padLen := aes.BlockSize - len(data)%aes.BlockSize
	padding := bytes.Repeat([]byte{byte(padLen)}, padLen)
	paddedData := append(data, padding...)

	// Encrypt the data
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}