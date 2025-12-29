package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData verschlüsselt die Daten mit dem Schlüssel unter Verwendung von AES im CBC-Modus.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// Sicherstellen, dass der Schlüssel mindestens 16 Bytes lang ist
	if len(key) < 16 {
		return nil, nil, nil, errors.New("der Schlüssel muss mindestens 16 Bytes lang sein")
	}

	// Verwenden des Präfixes des bereitgestellten Schlüssels, um den AES-Schlüssel zu generieren
	aesKey = key[:16]

	// Erzeugen eines neuen Initialisierungsvektors (IV)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Erstellen des AES-CBC-Ciphers
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Padding der Daten
	data = pad(data, aes.BlockSize)

	// Verschlüsseln der Daten
	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	encryptedData = ciphertext
	return encryptedData, iv, aesKey, nil
}

// pad fügt Padding zu den Daten hinzu, um sicherzustellen, dass sie ein Vielfaches der Blockgröße sind.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}