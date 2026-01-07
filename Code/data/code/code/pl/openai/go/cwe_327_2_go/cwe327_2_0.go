package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData Szyfruj dane za pomocą klucza, używając trybu CBC.
// Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Upewnij się, że długość klucza jest wystarczająca dla AES (16, 24 lub 32 bajty).
	if len(key) < 16 {
		return nil, nil, nil, errors.New("klucz musi mieć co najmniej 16 bajtów dla AES")
	}

	// Wybierz odpowiednią długość klucza (16 bajtów) dla AES.
	aesKey := key[:16]

	// Utwórz nową instancję AES.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Utwórz wektor inicjalizacji (IV).
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Paduj dane do długości bloku.
	pad := aes.BlockSize - len(data)%aes.BlockSize
	padding := bytes.Repeat([]byte{byte(pad)}, pad)
	data = append(data, padding...)

	// Utwórz tryb CBC.
	mode := cipher.NewCBCEncrypter(block, iv)

	// Zaszyfruj dane.
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}