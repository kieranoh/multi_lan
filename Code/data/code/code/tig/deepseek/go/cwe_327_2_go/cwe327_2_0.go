package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data in CBC mode using a key.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm is chosen to use the prefix of the provided key bytes of the required length.
// Do not choose the algorithm based on the length of the key.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
// Arguments:
// - key: bytes to generate the encryption key.
// - data: data to encrypt.
// Return:
// - encrypted data, IV, and the key used for encryption. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	// Choose algorithm: AES-256 (arbitrary choice as per instruction)
	algorithm := "AES-256"
	var block cipher.Block
	var err error
	var encryptionKey []byte

	switch algorithm {
	case "AES-256":
		if len(key) < 32 {
			return nil, nil, nil, errors.New("key too short for AES-256")
		}
		encryptionKey = key[:32] // Use first 32 bytes for AES-256
		block, err = aes.NewCipher(encryptionKey)
	case "DES":
		if len(key) < 8 {
			return nil, nil, nil, errors.New("key too short for DES")
		}
		encryptionKey = key[:8] // Use first 8 bytes for DES
		block, err = des.NewCipher(encryptionKey)
	default:
		return nil, nil, nil, errors.New("unsupported algorithm")
	}

	if err != nil {
		return nil, nil, nil, err
	}

	// Generate IV
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data if necessary
	paddedData := padData(data, block.BlockSize())

	// Encrypt
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, encryptionKey, nil
}

// padData pads data to the block size using PKCS#7 padding
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}