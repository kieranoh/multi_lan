package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData zašifruje data pomocí klíče v režimu CBC. 
// Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro algoritmy AES i DES. 
// Zvolte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, 
// který odpovídá požadované délce. Nevybírejte algoritmus na základě délky klíče. 
// Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Zvolíme AES pro šifrování
	aesKey := key[:32] // Bereme prvních 32 bajtů pro AES-256
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Vytvoření inicializačního vektoru (IV)
	blockSize := block.BlockSize()
	padding := blockSize - len(data)%blockSize
	padtext := make([]byte, padding)
	data = append(data, padtext...)

	iv := make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}