package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the data with the key using AES and CBC mode.
// The provided key bytes must be at least 16 bytes long.
// It uses the prefix of the provided key bytes that matches the required length.
// It returns the encrypted data, the IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// AES requires the key to be either 16, 24, or 32 bytes long.
	// Here we will use a key length of 16 bytes for AES-128.
	const keyLength = 16

	if len(key) < keyLength {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}
	
	// Use the prefix of the key that matches the required length
	aesKey = key[:keyLength]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate a new IV (initialization vector) for CBC mode
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad the data to be a multiple of the block size
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Encrypt the padded data using CBC mode
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}