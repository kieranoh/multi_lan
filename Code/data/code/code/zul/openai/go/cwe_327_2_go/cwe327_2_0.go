package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode with the provided key bytes.
// The key bytes must be at least 64 bytes long, but only the required prefix length for AES is used.
// It returns the encrypted data, initialization vector (IV), and the AES key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES requires a key length of 16, 24, or 32 bytes.
	// We will take the first 32 bytes of the key for AES.
	var aesKey []byte
	if len(key) < 32 {
		return nil, nil, nil, errors.New("provided key must be at least 32 bytes long for AES")
	}
	aesKey = key[:32]

	// Create a new AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Create a new IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	data = pad(data, aes.BlockSize)

	// Encrypt the data
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad adds PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}