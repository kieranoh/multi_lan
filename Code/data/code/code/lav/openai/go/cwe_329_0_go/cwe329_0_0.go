package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the data using AES in CBC mode with the given key.
// The provided key bytes must be long enough (>= 16 bytes). The prefix of the provided key bytes is used to match the required length.
// Returns the encrypted data, the IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 32 bytes of the key for AES-256
	var aesKeyBytes []byte
	if len(key) >= 32 {
		aesKeyBytes = key[:32]
	} else {
		aesKeyBytes = key[:32]
	}

	block, err := aes.NewCipher(aesKeyBytes)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// Encrypt the data in CBC mode
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKeyBytes, nil
}