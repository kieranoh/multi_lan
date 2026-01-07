package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// The provided key bytes must be sufficiently long (>= 16 bytes).
// The prefix of the provided key bytes is used to meet the required length.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is at least 16 bytes and truncate or use a prefix as needed
	const keySize = 16
	if len(key) < keySize {
		panic("key must be at least 16 bytes long")
	}
	aesKey = key[:keySize]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Create a new IV
	iv = make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Padding the data to be encrypted
	padding := keySize - len(data)%keySize
	padtext := append(data, byte(padding))
	for i := 0; i < padding-1; i++ {
		padtext = append(padtext, byte(padding))
	}

	// Encrypt the data
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey
}