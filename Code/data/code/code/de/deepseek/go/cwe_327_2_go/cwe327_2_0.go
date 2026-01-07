package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Verschlüsseln Sie die Daten mit dem Schlüssel im CBC-Modus.
// Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für sowohl AES- als auch DES-Algorithmen.
// Wählen Sie nur einen Algorithmus zur Implementierung und verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
// Wählen Sie den Algorithmus NICHT basierend auf der Länge des Schlüssels.
// Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.
// Argumente:
// - key: Die Bytes zur Generierung des Verschlüsselungsschlüssels.
// - data: Die zu verschlüsselnden Daten.
// Rückgabe:
// - Die verschlüsselten Daten, den IV und den für die Verschlüsselung verwendeten Schlüssel. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Wir wählen AES-256 für die Implementierung (festgelegte Wahl, unabhängig von der Schlüssellänge)
	const aesKeySize = 32 // 32 Bytes = 256 bits für AES-256

	// Überprüfen, ob der Schlüssel lang genug ist
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key ist nicht lang genug für AES-256 (mindestens 32 Bytes erforderlich)")
	}

	// Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes mit der erforderlichen Länge
	aesKey := make([]byte, aesKeySize)
	copy(aesKey, key[:aesKeySize])

	// Erstellen Sie den AES-Cipher-Block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Padding für die Daten hinzufügen, um Blockgröße zu erreichen
	paddedData := pkcs7Pad(data, block.BlockSize())

	// IV (Initialisierungsvektor) generieren
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Verschlüsselung im CBC-Modus durchführen
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pkcs7Pad fügt PKCS#7 Padding zu den Daten hinzu
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}