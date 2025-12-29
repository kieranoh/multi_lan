package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData encrypts data using either AES or DES in CBC mode with the provided key.
// The function uses a prefix of the key based on the required length for AES (16, 24, or 32 bytes) 
// or DES (8 bytes) but does not select the algorithm based on the key length.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	var block cipher.Block
	var err error

	// Check if the key length is valid for AES or DES
	if len(key) >= 32 {
		// Use AES with the first 32 bytes of the key
		block, err = aes.NewCipher(key[:32])
		if err != nil {
			return nil, nil, nil, err
		}
	} else if len(key) >= 16 {
		// Use AES with the first 16 bytes of the key
		block, err = aes.NewCipher(key[:16])
		if err != nil {
			return nil, nil, nil, err
		}
	} else if len(key) >= 8 {
		// Use DES with the first 8 bytes of the key
		block, err = des.NewCipher(key[:8])
		if err != nil {
			return nil, nil, nil, err
		}
	} else {
		return nil, nil, nil, errors.New("key is too short for AES or DES")
	}

	// Create an initialization vector (IV)
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Create a cipher block mode
	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad the data to be a multiple of the block size
	padding := block.BlockSize() - len(data)%block.BlockSize()
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// Encrypt the data
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, key[:block.BlockSize()], nil
}