package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData Szyfruj dane za pomocą klucza, używając AES i trybu CBC.
// Podany klucz bajtów jest wystarczająco długi (>= 64 bajty). Użyj prefiksu
// podanych bajtów klucza, który odpowiada wymaganemu rozmiarowi.
// Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
//
// Arguments:
// - key: Bajty do wygenerowania klucza szyfrowania (co najmniej 16 bajtów).
// - data: Dane do zaszyfrowania.
//
// Returns:
// - (encryptedData, iv, aesKey): Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}
	
	// Ustalanie rozmiaru klucza AES (16, 24, 32 bajty)
	aesKey = key[:16] // używamy pierwszych 16 bajtów klucza

	// Tworzenie nowego wektora inicjalizacji (IV)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Tworzenie nowego bloku AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Przygotowanie danych do szyfrowania (padding)
	data = pkcs7Padding(data, aes.BlockSize)

	// Szyfrowanie
	ciphertext := make([]byte, len(data))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, data)

	return ciphertext, iv, aesKey, nil
}

// pkcs7Padding dodaje padding do danych zgodnie z algorytmem PKCS#7
func pkcs7Padding(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}