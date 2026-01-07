package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/base64"
	"errors"
	"io"
)

// encryptData titkosítja az adatokat a megadott kulccsal CBC módban.
// A kulcs bájtok legalább 64 bájt hosszúak, és a titkosításhoz az AES algoritmust használja.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Ellenőrizzük, hogy a kulcs legalább 16 bájt hosszú-e
	if len(key) < 16 {
		return nil, nil, nil, errors.New("the key must be at least 16 bytes long")
	}

	// Válasszuk ki az AES kulcsot az első 16 bájtból
	aesKey := key[:16]

	// Generálj egy IV-t
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Hozzunk létre egy AES blokk titkosítót
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Padoljuk az adatokat, hogy a blokkok méretének megfelelő legyen
	data = pad(data, aes.BlockSize)

	// Csináljuk meg a CBC titkosítást
	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey, nil
}

// pad a bemeneti adatokat a megadott blokkméretnek megfelelően
func pad(data []byte, blockSize int) []byte {
	padLen := blockSize - (len(data) % blockSize)
	pad := bytes.Repeat([]byte{byte(padLen)}, padLen)
	return append(data, pad...)
}