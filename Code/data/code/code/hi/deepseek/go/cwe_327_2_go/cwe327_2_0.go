package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using CBC mode with a key derived from the provided key bytes.
// The function uses AES-256 encryption (32-byte key) and returns the encrypted data,
// initialization vector (IV), and the actual encryption key used.
// Arguments:
//   - key: Bytes to generate encryption key from (must be at least 32 bytes for AES-256)
//   - data: Data to encrypt
// Returns:
//   - Encrypted data, IV, encryption key used, and error (if any)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Validate input parameters
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// Use the first 32 bytes of the provided key for AES-256
	aesKey := key[:32]

	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate random IV (16 bytes for AES block size)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data to be multiple of block size
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Create CBC encryptor
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, aesKey, nil
}

// pkcs7Pad pads data to the specified block size using PKCS#7 padding
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}