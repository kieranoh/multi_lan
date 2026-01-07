package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData versleutelt de gegevens met de sleutel met behulp van de CBC-modus.
// Het gebruikt AES-algoritme en genereert een initialisatievector (IV).
// De lengte van de sleutel is ervan afhankelijk of deze minimaal 16 bytes is.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("de sleutel moet minimaal 16 bytes lang zijn voor AES")
	}

	// Gebruik alleen de eerste 16 bytes van de sleutel voor AES
	aesKey := key[:16]

	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Initialisatievector aanmaken
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad de data als dat nodig is
	paddedData := pad(data, aes.BlockSize)

	// Maak een nieuwe CBC modus
	mode := cipher.NewCBCEncrypter(block, iv)

	// Versleutel de data
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad voegt padding toe aan de data zodat deze een veelvoud is van de blokgrootte
func pad(src []byte, blockSize int) []byte {
	padding := blockSize - len(src)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(src, padtext...)
}