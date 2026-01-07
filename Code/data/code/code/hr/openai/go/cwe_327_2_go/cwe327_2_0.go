package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode.
// The provided key bytes should be at least 64 bytes long, but only the first
// 32 bytes will be used for the AES key.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES")
	}

	// Use the first 32 bytes of the key for AES
	aesKey := key[:32]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV (initialization vector)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new CBC encrypter
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	pad := bytes.Repeat([]byte{byte(padding)}, padding)
	paddedData := append(data, pad...)

	// Encrypt the data
	encryptedData := make([]byte, len(paddedData))
	cbc.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}