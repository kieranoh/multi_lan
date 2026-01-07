package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData salakirjoittaa tiedot avaimella käyttäen CBC-tilaa.
// Annetut avainbittit ovat tarpeeksi pitkiä (>= 64 tavua) sekä AES- että DES-algoritmeille.
// Valitse vain yksi algoritmi toteutettavaksi ja käytä annettujen avainbittien prefiksiä, joka vastaa vaadittua pituutta.
// Älä valitse algoritmia avaimen pituuden perusteella.
// Palauta salattu data, IV (alkuvarausvektori) ja salaukseen käytetty avain.
// Arguments:
// - key: Tavut salausavaimen luomiseksi.
// - data: Salattava data.
// Return:
// - Salattu data, IV ja salaukseen käytetty avain. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes for AES")
	}

	// Rajaa avain AES:n vaatimaan pituuteen
	aesKey := key[:16]

	// Luo AES-salausobjekti
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Luodaan IV
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Luo CBC-tilan salaaja
	mode := cipher.NewCBCEncrypter(block, iv)

	// Täydennä data 16 tavun lohkoihin
	paddedData := pad(data)

	// Salakirjoita data
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad täyttää datan 16 tavun lohkoihin
func pad(data []byte) []byte {
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}