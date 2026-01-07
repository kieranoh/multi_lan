package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"fmt"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode with the provided key.
// The provided key bytes must be at least 16 bytes long.
// It returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is at least 16 bytes
	if len(key) < 16 {
		panic("Key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key
	aesKey = key[:16]

	// Create a new AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Create a new IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad the data to be a multiple of the block size
	paddedData := pad(data, aes.BlockSize)

	// Create a CBC encrypter
	mode := cipher.NewCBCEncrypter(block, iv)

	// Encrypt the data
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pad adds padding to the data to make its length a multiple of blockSize
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}

// Example usage
func main() {
	key := []byte("thisisaverysecretkey123456") // Example key (must be at least 16 bytes)
	data := []byte("Hello, World!")

	encryptedData, iv, aesKey := encryptData(key, data)
	fmt.Printf("Encrypted Data: %s\n", base64.StdEncoding.EncodeToString(encryptedData))
	fmt.Printf("IV: %s\n", base64.StdEncoding.EncodeToString(iv))
	fmt.Printf("AES Key: %s\n", base64.StdEncoding.EncodeToString(aesKey))
}