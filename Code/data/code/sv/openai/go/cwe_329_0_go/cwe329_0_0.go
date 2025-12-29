package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData krypterar datan med nyckeln med hjälp av AES och CBC-läge.
// De angivna nyckelbytes är tillräckligt långa (>= 16 bytes). Använd prefixet av
// de angivna nyckelbytes som matchar den erforderliga längden.
// Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som
// användes för kryptering.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes")
	}

	// Skapa en AES-blockchiffer
	aesKey = key[:16] // Använd de första 16 bytes av nyckeln
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Skapa en IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding av data för att matcha blockstorleken
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Kryptering i CBC-läge
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}