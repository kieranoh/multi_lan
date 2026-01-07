package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData versleutelt de gegevens met de sleutel met behulp van de CBC-modus.
// De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes) voor zowel AES- als DES-algoritmen.
// Kies slechts één algoritme om te implementeren en gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
// Kies het algoritme NIET op basis van de lengte van de sleutel.
// Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.
// Argumenten:
// - key: De bytes om de versleutelingssleutel te genereren.
// - data: De te versleutelen gegevens.
// Terugkeer:
// - De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Kies AES-256 als algoritme (onafhankelijk van sleutellengte)
	const aesKeySize = 32 // 32 bytes = 256 bits voor AES-256

	// Controleer of de sleutel lang genoeg is
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key is too short for AES-256")
	}

	// Neem het voorvoegsel van de sleutel met de vereiste lengte
	aesKey := key[:aesKeySize]

	// Maak een nieuw AES cipher blok
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Genereer een willekeurige IV (initialisatievector)
	iv := make([]byte, aes.BlockSize) // AES blokgrootte is 16 bytes
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad de data om een veelvoud van de blokgrootte te krijgen
	paddedData := padData(data, aes.BlockSize)

	// Versleutel de data in CBC-modus
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData voegt PKCS#7 padding toe aan de data om een veelvoud van blockSize te krijgen
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}