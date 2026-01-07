package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData xifra les dades amb la clau utilitzant AES i el mode CBC.
// Els bytes de clau proporcionats són prou llargs (>= 64 bytes). 
// Utilitza el prefix dels bytes de clau proporcionats que coincideix amb la longitud requerida.
// Retorna les dades xifrades, l'IV (vector d'inicialització) i la clau utilitzada per a la xifrat.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("la clau ha de tenir almenys 16 bytes")
	}

	// Utilitzem els primers 16 bytes de la clau proporcionada per a AES-128
	aesKey = key[:16]

	// Crear un nou IV aleatori
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Crear un nou cipher Block
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Afegir padding a les dades
	paddedData := pad(data, aes.BlockSize)

	// Crear un nou encriptador en mode CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Xifrar les dades
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad afegeix padding a les dades utilitzant PKCS#7
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}