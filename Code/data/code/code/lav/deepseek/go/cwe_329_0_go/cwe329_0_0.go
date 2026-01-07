package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key bytes.
// The provided key bytes must be sufficiently long (>= 64 bytes). The function uses
// a prefix of the provided key bytes to match the required length.
// It returns the encrypted data, the initialization vector (IV), and the AES key used.
//
// Arguments:
//   - key: bytes from which to derive the encryption key (minimum 16 bytes).
//   - data: data to be encrypted.
//
// Returns:
//   - encryptedData: the encrypted data.
//   - iv: the initialization vector used.
//   - aesKey: the AES key derived from the provided key bytes.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Validate key length
	if len(key) < 16 {
		panic("key must be at least 16 bytes long")
	}

	// Derive a 32-byte AES key (for AES-256) from the provided key bytes
	// Use SHA-256 to ensure consistent key length
	hash := sha256.New()
	hash.Write(key)
	aesKey = hash.Sum(nil) // 32 bytes for AES-256

	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Generate random IV
	iv = make([]byte, aes.BlockSize) // 16 bytes for AES
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad data to be multiple of block size
	paddedData := padPKCS7(data, aes.BlockSize)

	// Encrypt the data
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// padPKCS7 pads data to the specified block size using PKCS#7 padding.
func padPKCS7(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}