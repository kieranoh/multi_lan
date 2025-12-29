package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData šifrira podatke koristeći AES-256 u CBC načinu rada.
// Koristi prvi 32 bajta predanog ključa za AES-256 ključ i generira nasumični IV.
// Vraća šifrirane podatke, IV, korišteni AES ključ i eventualnu grešku.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Provjeri da li je ključ dovoljno dug za AES-256 (32 bajta)
	if len(key) < 32 {
		return nil, nil, nil, errors.New("ključ mora imati barem 32 bajta za AES-256")
	}

	// Izvuci prvih 32 bajta za AES-256 ključ
	aesKey := key[:32]

	// Stvori AES šifru
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generiraj nasumični IV (16 bajta za AES)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pripremi podatke za šifriranje (PKCS7 padding)
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Šifriraj podatke u CBC načinu
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, aesKey, nil
}

// pkcs7Pad dodaje PKCS7 padding podacima do zadane duljine bloka.
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}