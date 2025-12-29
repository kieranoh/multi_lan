package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData Kryptera datan med nyckeln med hjälp av CBC-läge.
// De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för både AES- och DES-algoritmerna.
// Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden.
// Välj INTE algoritmen baserat på nyckellängden.
// Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Vi väljer AES, som kräver en nyckellängd av 16, 24 eller 32 bytes.
	var aesKey []byte
	if len(key) >= 32 {
		aesKey = key[:32] // 256-bit AES
	} else if len(key) >= 24 {
		aesKey = key[:24] // 192-bit AES
	} else if len(key) >= 16 {
		aesKey = key[:16] // 128-bit AES
	} else {
		return nil, nil, nil, errors.New("key length is insufficient for AES")
	}

	// Skapa en ny AES-cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Skapa en IV (initialiseringsvektor)
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Skapa en ny CBC-mode
	mode := cipher.NewCBCEncrypter(block, iv)

	// Pad data för att vara en multipel av blockstorleken
	padding := block.BlockSize() - len(data)%block.BlockSize()
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// Kryptera datan
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}