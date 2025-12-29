package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData xifra les dades amb la clau utilitzant el mode CBC.
// Els bytes de clau proporcionats són prou llargs (>= 64 bytes) per als algorismes AES i DES.
// En aquesta implementació, s'utilitza l'algorisme AES.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Comprovem que la longitud de la clau és adequada per AES (16, 24 o 32 bytes).
	if len(key) < 16 {
		return nil, nil, nil, errors.New("la clau ha de tenir almenys 16 bytes per AES")
	}
	aesKey := key[:32] // Tria la longitud adequada per AES (32 bytes)

	// Crea un nou cipher AES.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Genera un IV aleatori.
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Crea un nou mode CBC.
	mode := cipher.NewCBCEncrypter(block, iv)

	// Omple les dades a xifrar amb zero si no són un múltiple de la longitud del bloc.
	padding := block.BlockSize() - len(data)%block.BlockSize()
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	data = append(data, padtext...)

	// Xifra les dades.
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}