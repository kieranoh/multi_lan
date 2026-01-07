package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts the given data using AES in CBC mode with the provided key.
// The key must be at least 16 bytes, and its prefix is used to meet the required length.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Use the first 16 bytes of the key for AES-128
	aesKey = key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad data to be a multiple of the block size
	pad := aes.BlockSize - len(data)%aes.BlockSize
	padding := bytes.Repeat([]byte{byte(pad)}, pad)
	data = append(data, padding...)

	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}