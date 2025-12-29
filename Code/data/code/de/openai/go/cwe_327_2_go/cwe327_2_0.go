package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData verschlüsselt die Daten mit dem Schlüssel im CBC-Modus.
// Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für sowohl AES- als auch DES-Algorithmen.
// Diese Implementierung verwendet jedoch nur AES.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// AES benötigt einen Schlüssel von 16, 24 oder 32 Bytes
	aesKey := key[:32] // Verwenden der ersten 32 Bytes für AES

	// Erstellen Sie eine AES-Block-Instanz
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Erstellen Sie einen IV (Initialisierungsvektor) für den CBC-Modus
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding der Daten, um sicherzustellen, dass sie das Blockgrößenformat erfüllen
	data = pad(data, aes.BlockSize)

	// Erstellen Sie ein Cipher-Block-Mode-Objekt
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Verschlüsseln der Daten
	encryptedData := make([]byte, len(data))
	cbc.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad fügt Padding zu den Daten hinzu, um die Blockgröße zu erfüllen
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}