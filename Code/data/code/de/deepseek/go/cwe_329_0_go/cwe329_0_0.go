import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Verschlüsseln Sie die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwenden Sie das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Geben Sie die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

Arguments:
- key: Die Bytes zur Generierung des Verschlüsselungsschlüssels (mindestens 16 Bytes).
- data: Die zu verschlüsselnden Daten.

Returns:
- (encryptedData, iv, aesKey): Die verschlüsselten Daten, der IV und der für die Verschlüsselung verwendete Schlüssel. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256 benötigt einen 32-Byte-Schlüssel
	keyLength := 32
	if len(key) < keyLength {
		// Fallback: Verwende den gesamten Schlüssel und fülle mit Nullen auf
		aesKey = make([]byte, keyLength)
		copy(aesKey, key)
	} else {
		// Verwende das Präfix der angegebenen Länge
		aesKey = key[:keyLength]
	}

	// Erstelle einen neuen AES-Cipher-Block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err) // In einer realen Anwendung sollte dies besser behandelt werden
	}

	// Erzeuge einen zufälligen IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err) // In einer realen Anwendung sollte dies besser behandelt werden
	}

	// PKCS7-Padding auf die Daten anwenden
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Verschlüssele die Daten im CBC-Modus
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// Hilfsfunktion für PKCS7-Padding
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}