package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData krypterar datan med nyckeln med hjälp av CBC-läge.
// De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för både AES- och DES-algoritmerna.
// Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden.
// Välj INTE algoritmen baserat på nyckellängden.
// Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.
// Arguments:
// - key: Bytesen för att generera krypteringsnyckeln.
// - data: Datan som ska krypteras.
// Return:
// - Den krypterade datan, IV och nyckeln som användes för kryptering. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Välj AES-256 som algoritm (kräver 32 byte nyckel)
	const aesKeyLength = 32
	
	// Kontrollera att nyckeln är tillräckligt lång
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("nyckeln är för kort för AES-256, kräver minst 32 byte")
	}
	
	// Använd prefixet av nyckeln för att skapa AES-nyckeln
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])
	
	// Skapa AES-cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// Skapa IV (initialiseringsvektor)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// PKCS7-padding för att matcha blockstorleken
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}
	
	// Kryptera datan med CBC-läge
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey, nil
}