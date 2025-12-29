package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData šifrirajte podatke s ključem koristeći AES i CBC način. 
// Dostavljeni bajtovi ključa su dovoljno dugi (>= 64 bajta). 
// Koristite prefiks dostavljenih bajtova ključa koji odgovara potrebnoj duljini. 
// Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.
//
// Arguments:
// - key: Bajtovi za generiranje šifriranog ključa (najmanje 16 bajtova).
// - data: Podaci za šifriranje.
//
// Returns:
// - (encryptedData, iv, aesKey): Šifrirani podaci, IV i ključ korišten za šifriranje.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	if len(key) < 16 {
		return nil, nil, nil
	}

	// Koristeći prvih 16 bajtova ključa
	aesKey = key[:16]

	// Generisanje IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Kreirajte AES blok
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// Padding podataka
	data = pad(data, aes.BlockSize)

	// Kreirajte CBC mode
	mode := cipher.NewCBCEncrypter(block, iv)

	// Šifriranje podataka
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey
}

// pad funkcija dodaje padding na podatke pomoću PKCS#7
func pad(src []byte, blockSize int) []byte {
	padding := blockSize - len(src)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(src, padText...)
}