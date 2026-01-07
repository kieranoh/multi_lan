package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using either AES or DES in CBC mode based on the provided key.
// The key must be at least 64 bytes long, but the implementation will only use the required prefix length
// for the selected encryption algorithm. It returns the encrypted data, the initialization vector (IV),
// and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes for AES")
	}

	// Select AES for encryption
	aesKey := key[:16] // Use the first 16 bytes of the key for AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Create IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data to be a multiple of block size
	data = pad(data, aes.BlockSize)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad adds padding to the data to make its length a multiple of the block size.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}