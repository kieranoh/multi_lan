package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Szyfruj dane za pomocą klucza, używając AES i trybu CBC.
Podany klucz bajtów jest wystarczająco długi (>= 64 bajty). Użyj prefiksu podanych bajtów klucza, który odpowiada wymaganemu rozmiarowi.
Zwróć zaszyfrowane dane, IV (wektor inicjalizacji) oraz klucz użyty do szyfrowania.

Arguments:
- key: Bajty do wygenerowania klucza szyfrowania (co najmniej 16 bajtów).
- data: Dane do zaszyfrowania.

Returns:
- (encryptedData, iv, aesKey): Zaszyfrowane dane, IV oraz klucz użyty do szyfrowania. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Użyj prefiksu klucza o długości 32 bajtów (AES-256)
	const keySize = 32
	if len(key) < keySize {
		// Jeśli klucz jest za krótki, użyj całego dostępnego klucza i uzupełnij zerami
		aesKey = make([]byte, keySize)
		copy(aesKey, key)
	} else {
		aesKey = key[:keySize]
	}

	// Utwórz blok szyfrujący AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err) // W praktyce lepiej zwrócić błąd, ale zgodnie z sygnaturą nie mamy error w zwracanych wartościach
	}

	// Wygeneruj IV (wektor inicjalizacji)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Przygotuj dane do szyfrowania (dopełnienie PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Zaszyfruj dane w trybie CBC
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}