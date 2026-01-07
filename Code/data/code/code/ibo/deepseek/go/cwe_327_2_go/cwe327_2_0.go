package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data in CBC mode using a key.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm is chosen to use the prefix of the provided key bytes of the required length.
// The algorithm is not selected based on the length of the key.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
// Arguments:
// - key: Bytes to generate the encryption key.
// - data: Data to be encrypted.
// Return:
// - Encrypted data, IV, and the key used for encryption. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Validate input parameters
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}
	if data == nil {
		return nil, nil, nil, errors.New("data cannot be nil")
	}

	// Choose AES algorithm (as per requirement, we choose one algorithm regardless of key length)
	// Use the first 32 bytes of the key for AES-256
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("key is too short for AES-256")
	}
	aesKey := key[:aesKeyLength]

	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate random IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data to be multiple of block size
	paddedData := padPKCS7(data, aes.BlockSize)

	// Create CBC encryptor
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
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