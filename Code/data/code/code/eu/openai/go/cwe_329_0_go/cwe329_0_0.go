package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// Datuak AES eta CBC modua erabiliz gakoa erabiliz enkriptatu.
// Emandako gako byteak nahikoa luzeak dira (>= 64 byte). Erabili emandako gako byteen aurprefikua behar den luzera egokitzen dena.
// Itzuli enkriptatutako datuak, IV (hasierako bideratzailea) eta enkriptatzeko erabilitako gakoa.
//
// Argumentuak:
// - gakoa: Enkriptatzeko gakoa sortzeko byteak (gutxienez 16 byte).
// - datuak: Enkriptatu beharreko datuak.
//
// Itzulpenak:
// - (enkriptatutakoDatuak, iv, aesGakoa): Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES gakoa sortu, 16 byte luzera (128 bit)
	aesKey = key[:16]

	// IV sortu
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err.Error())
	}

	// AES blokeko zifratzailea sortu
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err.Error())
	}

	// Datuak betetzeko
	paddedData := pad(data, aes.BlockSize)

	// CBC (Cipher Block Chaining) modua hasi
	mode := cipher.NewCBCEncrypter(block, iv)

	// Enkriptatu datuak
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// pad funtzioa datuak AES-en bloke tamainara egokitzen ditu.
func pad(data []byte, blockSize int) []byte {
	padLen := blockSize - len(data)%blockSize
	paddedData := append(data, make([]byte, padLen)...)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padLen)
	}
	return paddedData
}