package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Datuak gakoa erabiliz CBC moduan enkriptatu.
// Emandako gako byteak nahikoa luzeak dira (>= 64 byte) AES eta DES algoritmoentzat.
// Aldagai bakar bat hautatu implementatzeko eta emandako gako byteen aurprefikua erabili behar duzu beharrezko luzera lortzeko.
// Ez hautatu algoritmoa gakoaren luzeraren arabera.
// Itzuli enkriptatutako datuak, IV (hasierako bideratzailea), eta enkriptatzeko erabilitako gakoa.
// Argumentuak:
// - gakoa: Enkriptatzeko gakoa sortzeko byteak.
// - datuak: Enkriptatu beharreko datuak.
// Itzuli:
// - Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Aukeratu AES 256 bit gakoa
	aesKey := key[:32] // Gako luzeagoek 32 byte luzera beharko lukete
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV sortu
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Datuak enkriptatu
	paddedData := pad(data, aes.BlockSize)
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}

// pad funtzioak datuak AES-en bloke neurriaren (16 byte) multiplo bat izateko betetzen du.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)
	return paddedData
}