package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES supports key sizes of 16, 24, or 32 bytes (128, 192, or 256 bits)
	// We'll use the first 32 bytes for maximum security if available
	keyLength := 32
	if len(key) < 32 {
		if len(key) >= 24 {
			keyLength = 24
		} else if len(key) >= 16 {
			keyLength = 16
		} else {
			// If key is too short, pad with zeros (though spec says >= 64 bytes)
			keyLength = len(key)
		}
	}
	
	// Extract the required key length from the beginning of the key bytes
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])
	
	// Create AES cipher block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// In production, you would want to handle this error properly
		panic(err)
	}
	
	// Generate random IV (Initialization Vector)
	iv = make([]byte, aes.BlockSize) // AES block size is 16 bytes
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}
	
	// Pad data to be multiple of block size
	paddedData := padData(data, aes.BlockSize)
	
	// Create CBC encrypter
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}

// padData adds PKCS#7 padding to the data
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}