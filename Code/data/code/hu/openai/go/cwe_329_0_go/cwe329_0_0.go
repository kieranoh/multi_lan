package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData titkosítja az adatokat a kulccsal AES és CBC módban.
// A megadott kulcs bájtok elég hosszúak (>= 64 bájt). Használja a megadott kulcs bájtok olyan előtagját, amely megfelel a szükséges hosszúságnak.
// Adja vissza a titkosított adatokat, az IV-t (kezdeti vektor) és a titkosításhoz használt kulcsot.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Az AES kulcs hossza 16, 24 vagy 32 byte lehet. Itt a kulcs első 16 byte-ját használjuk.
	aesKey = key[:16]

	// Létrehozzuk az IV-t
	iv = make([]byte, aes.BlockSize)
	if _, err = io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Létrehozzuk az AES titkosítót
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Padding a plaintext adatokhoz
	data = pad(data, aes.BlockSize)

	// CBC mód inicializálása
	cbc := cipher.NewCBCEncrypter(block, iv)

	// Titkosítás
	encryptedData = make([]byte, len(data))
	cbc.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad hozzáadja a paddingot a titkosítandó adatokhoz
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}