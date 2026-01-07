package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the provided data using AES in CBC mode with the given key.
// The provided key bytes must be long enough (>= 16 bytes). The prefix of the provided
// key bytes is used to match the required length.
// It returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// Check if key is at least 16 bytes long.
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key (AES-128).
	aesKey = key[:16]

	// Create a new AES cipher.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Create IV (Initialization Vector) for CBC mode.
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size.
	paddedData := pad(data, aes.BlockSize)

	// Create a cipher.BlockMode for CBC mode.
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data.
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad adds padding to the data to ensure its length is a multiple of blockSize.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}