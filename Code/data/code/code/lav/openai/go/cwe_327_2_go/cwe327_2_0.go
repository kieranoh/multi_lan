package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the data using AES in CBC mode with the provided key.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm will be implemented, and the prefix of the provided key bytes will be used according to the required length.
// The function does not choose the algorithm based on the length of the key.
// It returns the encrypted data, the IV (initialization vector), and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES requires a key length of 16, 24, or 32 bytes
	var aesKey []byte
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key is too short for AES encryption")
	}

	if len(key) <= 16 {
		aesKey = key[:16]
	} else if len(key) <= 24 {
		aesKey = key[:24]
	} else {
		aesKey = key[:32]
	}

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a new CBC encrypter
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// Encrypt the data
	encryptedData := make([]byte, len(data))
	cbc.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}