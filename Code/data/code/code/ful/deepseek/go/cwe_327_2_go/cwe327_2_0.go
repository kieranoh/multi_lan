package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data in CBC mode using a key derived from the provided key bytes.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm is chosen to use the prefix of the provided key bytes of the required length.
// The algorithm is not selected based on the length of the key.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
// Arguments:
// - key: bytes to generate the encryption key.
// - data: data to encrypt.
// Return:
// - encrypted data, IV, encryption key, and error.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	// Choose AES-256 algorithm (32-byte key)
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("key too short for AES-256")
	}
	aesKey := key[:aesKeyLength]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generate IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data if necessary
	paddedData := padData(data, aes.BlockSize)

	// Encrypt data
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData pads data to the specified block size using PKCS#7 padding.
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}