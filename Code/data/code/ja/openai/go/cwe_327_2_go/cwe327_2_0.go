package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode.
// It uses the provided key, truncating it to 16 bytes if it exceeds that length.
// It returns the encrypted data, the initialization vector (IV), and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes for AES")
	}

	// Use the first 16 bytes of the key for AES encryption
	aesKey := key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Create a new IV
(iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	paddedData := pad(data, aes.BlockSize)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad adds padding to the data to make it a multiple of the block size
func pad(data []byte, blocksize int) []byte {
	padding := blocksize - len(data)%blocksize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}