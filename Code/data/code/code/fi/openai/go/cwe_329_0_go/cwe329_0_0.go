package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData salakirjoittaa tiedot avaimella käyttäen AES:ää ja CBC-tilaa.
// Annat avainbittit ovat tarpeeksi pitkiä (>= 16 tavua). Käytä annettujen avainbittien etuliitettä, joka vastaa vaadittua pituutta.
// Palauta salattu data, IV (alkuvektori) ja salaukseen käytetty avain.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key length must be at least 16 bytes")
	}

	// Luo AES-salausavain (16, 24 tai 32 tavua)
	aesKey = key[:16] // Käytetään vain ensimmäisiä 16 tavua

	// Luo uusi IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Luo AES-salaus
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Täydennä data AES-lohkomuotoon
	paddedData := pad(data)

	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}

// pad lisää täytteitä dataan AES-lohkon muotoon sopivaksi
func pad(data []byte) []byte {
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}