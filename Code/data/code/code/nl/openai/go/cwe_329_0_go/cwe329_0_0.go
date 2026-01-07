package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData versleutelt de gegevens met de sleutel met behulp van AES en CBC-modus.
// De opgegeven sleutelbytes zijn lang genoeg (>= 16 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
// Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.
//
// Arguments:
// - key: De bytes om de versleuteling sleutel te genereren (minimaal 16 bytes).
// - data: De te versleutelen gegevens.
//
// Returns:
// - (encryptedData, iv, aesKey): De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes")
	}

	// Gebruik de eerste 16 bytes van de sleutel
	aesKey = key[:16]

	// Genereer een IV (initialisatievector)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Maak een nieuw AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Maak een nieuwe CBC en pad de data
	paddedData := pad(data)
	ciphertext := make([]byte, len(paddedData))

	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}

// pad voegt padding toe aan de gegevens volgens PKCS#7
func pad(data []byte) []byte {
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}