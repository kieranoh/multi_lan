package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES and CBC mode with the provided key bytes.
// The provided key bytes must be at least 16 bytes long. The prefix of the provided key bytes
// is used to meet the required length.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the prefix of the key to ensure it's at least 16 bytes long.
	aesKey = key[:16]

	// Create a new AES cipher.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV (Initialization Vector) for the encryption.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new CBC encrypter.
	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size.
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, byte(padding))
	for i := 1; i < padding; i++ {
		paddedData = append(paddedData, byte(padding))
	}

	// Encrypt the data.
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}