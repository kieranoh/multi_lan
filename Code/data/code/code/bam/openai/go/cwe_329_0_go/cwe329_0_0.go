package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the provided data using AES and CBC mode with the given key.
// The provided key bytes must be at least 16 bytes long. The prefix of the provided key bytes
// will be used to meet the required length.
// It returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a random IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padText...)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}