package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"io"
)

// encryptData Zašifrujte data s klíčem pomocí AES a režimu CBC. Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů). Použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. Vraťte zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.
// Arguments:
// - key: Bajty pro generování šifrovacího klíče (alespoň 16 bajtů).
// - data: Data k zašifrování.
// Returns:
// - (encryptedData, iv, aesKey): Zašifrovaná data, IV a klíč použitý pro šifrování.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Vyberte správnou délku klíče (AES podporuje 16, 24, nebo 32 bajtů)
	var keyLength = 32 // 256 bitů, změní se podle potřeby na 16 nebo 24
	aesKey = key[:keyLength]

	// Vytvořte inicializační vektor (IV)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err.Error())
	}

	// Vytvořte nový blok AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err.Error())
	}

	// Připravte data na zašifrování
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Vytvořte nový cypher a zašifrujte
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(padtext))
	mode.CryptBlocks(encryptedData, padtext)

	return encryptedData, iv, aesKey
}