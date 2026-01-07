package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key bytes.
// The provided key bytes should be at least 64 bytes long and are truncated if necessary.
// It returns the encrypted data, the IV used for encryption, and the key used in the encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes for AES")
	}

	// Use only the first 16 bytes of the key for AES
	aesKey := key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV should be equal to the block size
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padText...)

	// Create a new CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}