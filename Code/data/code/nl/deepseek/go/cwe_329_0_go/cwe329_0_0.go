package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Versleutel de gegevens met de sleutel met behulp van AES en CBC-modus.
De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes). Gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte.
Geef de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt terug.

Arguments:
- key: De bytes om de versleuteling sleutel te genereren (minimaal 16 bytes).
- data: De te versleutelen gegevens.

Returns:
- (encryptedData, iv, aesKey): De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256 vereist een sleutel van 32 bytes (256 bits)
	const aesKeyLength = 32

	// Neem het voorvoegsel van de sleutel met de vereiste lengte
	if len(key) < aesKeyLength {
		// Als de sleutel te kort is, vul aan met nullen (dit zou niet moeten voorkomen volgens de specificatie)
		aesKey = make([]byte, aesKeyLength)
		copy(aesKey, key)
	} else {
		aesKey = key[:aesKeyLength]
	}

	// Maak een nieuw AES cipher blok
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// In geval van fout, retourneer lege slices
		return nil, nil, nil
	}

	// Genereer een willekeurige IV van 16 bytes (AES blokgrootte)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Pad de data naar een veelvoud van de blokgrootte
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Versleutel de data met CBC modus
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pkcs7Pad voegt PKCS#7 padding toe aan de data
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}