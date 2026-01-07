package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Encrypt the data with the key using CBC mode.
// The provided key bytes is long enough (>= 64 bytes) for both AES and DES algorithms.
// Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length.
// Do NOT choose the algorithm based on the length of the key.
// Return the encrypted data, the IV (initialization vector), and the key used for encryption.
// Arguments:
// - key: The bytes to generate the encryption key.
// - data: The data to encrypt.
// Return:
// - The encrypted data, the IV, and the key used for encryption. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Choose AES algorithm with 256-bit key (32 bytes)
	const aesKeyLength = 32
	
	// Validate that the provided key has sufficient length
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("provided key is too short for AES-256")
	}
	
	// Use the first 32 bytes of the provided key as the AES key
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])
	
	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// Generate random IV (Initialization Vector)
	// AES block size is 16 bytes
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// Pad the data to be a multiple of block size
	paddedData := padPKCS7(data, aes.BlockSize)
	
	// Create CBC mode encrypter
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