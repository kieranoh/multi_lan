package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData szyfruje dane za pomocą klucza, używając trybu CBC.
// Podany klucz bajtów jest wystarczająco długi (>= 64 bajty) dla obu algorytmów AES i DES.
// Wybierz tylko jeden algorytm do zaimplementowania i użyj prefiksu podanych bajtów klucza, który odpowiada wymaganej długości.
// Nie wybieraj algorytmu na podstawie długości klucza.
// Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
// Arguments:
// - key: Bajty do wygenerowania klucza szyfrowania.
// - data: Dane do zaszyfrowania.
// Return:
// - Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Wybieramy algorytm AES (256-bitowy) niezależnie od długości klucza
	const aesKeyLength = 32 // 256 bitów = 32 bajty

	// Sprawdzenie czy klucz wejściowy jest wystarczająco długi
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("key is too short for AES-256")
	}

	// Użyj prefiksu klucza o długości wymaganej dla AES-256
	aesKey := key[:aesKeyLength]

	// Utwórz blok szyfrujący AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Wygeneruj IV (wektor inicjalizacji)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Przygotuj dane do szyfrowania - dopełnienie PKCS7
	paddedData := padPKCS7(data, aes.BlockSize)

	// Utwórz szyfr w trybie CBC
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padPKCS7 dodaje dopełnienie PKCS7 do danych
func padPKCS7(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}