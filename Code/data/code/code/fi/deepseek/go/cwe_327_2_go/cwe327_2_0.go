package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Salakirjoita tiedot avaimella käyttäen CBC-tilaa.
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
	// Valitaan AES-256 algoritmi (ei valita avaimen pituuden perusteella)
	const aesKeySize = 32 // 256 bittiä = 32 tavua
	
	// Tarkistetaan että avain on tarpeeksi pitkä
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("avain on liian lyhyt, tarvitaan vähintään 32 tavua")
	}
	
	// Otetaan ensimmäiset 32 tavua avaimesta AES-256 avaimeksi
	aesKey := make([]byte, aesKeySize)
	copy(aesKey, key[:aesKeySize])
	
	// Luodaan AES-salausalgoritmi
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}
	
	// Luodaan satunnainen IV (Initialization Vector)
	// AES:n lohkokoko on 16 tavua, joten IV on saman kokoinen
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}
	
	// Täytetään data PKCS#7-täytöllä
	paddedData := pkcs7Pad(data, aes.BlockSize)
	
	// Salataan data CBC-tilassa
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey, nil
}

// pkcs7Pad täyttää datan PKCS#7-täytöllä
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}