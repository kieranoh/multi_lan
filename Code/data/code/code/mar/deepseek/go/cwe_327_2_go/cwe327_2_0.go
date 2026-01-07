package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data using AES-256 in CBC mode.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm is implemented (AES-256), using the prefix of the provided key bytes
// to the required length.
// The algorithm is not selected based on the length of the key.
// Returns the encrypted data, IV, and the key used for encryption.
// Arguments:
// - key: bytes to generate encryption key.
// - data: data to encrypt.
// Return:
// - encrypted data, IV, and the key used for encryption. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Validate input parameters
	if len(key) < 32 {
		return nil, nil, nil, errors.New("key must be at least 32 bytes for AES-256")
	}
	if data == nil {
		return nil, nil, nil, errors.New("data cannot be nil")
	}

	// Use first 32 bytes of the provided key for AES-256
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
	paddedData := padPKCS7(data, aes.BlockSize)

	// Create CBC encrypter
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, aesKey, nil
}

// padPKCS7 pads data to the specified block size using PKCS#7 padding
func padPKCS7(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}