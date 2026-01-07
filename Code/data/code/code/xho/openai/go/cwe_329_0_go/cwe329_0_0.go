package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// The provided key bytes must be long enough (>= 16 bytes). 
// The prefix of the provided key bytes is used to meet the required length.
// It returns the encrypted data, IV (initialization vector), and the key used for encryption.
//
// Arguments:
// - key: a byte slice used to generate the encryption key (minimum 16 bytes).
// - data: the data to encrypt.
//
// Returns:
// - (encryptedData, iv, aesKey): encrypted data, IV, and the key used for encryption.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Ensure the key is at least 16 bytes long
	if len(key) < 16 {
		return nil, nil, nil
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	// Create a new AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// Generate a new IV (initialization vector)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Pad the data to be a multiple of the block size
	data = pad(data, aes.BlockSize)

	// Create a new CBC encrypter
	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey
}

// pad adds PKCS#7 padding to the data
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}

func main() {
	// Example usage
	key := []byte("thisisaverysecretkey123456") // Example key (32 bytes)
	data := []byte("This is a secret message.")
	encryptedData, iv, aesKey := encryptData(key, data)
	fmt.Printf("Encrypted Data: %x\nIV: %x\nAES Key: %x\n", encryptedData, iv, aesKey)
}