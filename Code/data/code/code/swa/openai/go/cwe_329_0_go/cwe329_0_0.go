package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// The provided key bytes must be at least 16 bytes long. 
// The prefix of the provided key bytes is used to meet the required length.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// Ensure the key is at least 16 bytes long
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	// Create a new AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Prepare IV (Initialization Vector)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, byte(padding))
	for i := 0; i < padding-1; i++ {
		padtext = append(padtext, byte(padding))
	}

	// Encrypt the data
	encryptedData = make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey, nil
}