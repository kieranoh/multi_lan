package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData cripta i dati con la chiave utilizzando la modalità CBC.
// I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per entrambi gli algoritmi AES e DES.
// Scegli solo un algoritmo da implementare e utilizza il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
// NON scegliere l'algoritmo in base alla lunghezza della chiave.
// Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
// Arguments:
// - key: I byte per generare la chiave di crittografia.
// - data: I dati da crittografare.
// Return:
// - I dati crittografati, l'IV e la chiave utilizzata per la crittografia. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Verifica che la chiave sia sufficientemente lunga
	if len(key) < 64 {
		return nil, nil, nil, errors.New("la chiave deve essere almeno di 64 byte")
	}

	// Scelgo AES-256 (32 byte = 256 bit) come algoritmo fisso
	const aesKeyLength = 32
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// Crea il cifrario AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Genera un IV casuale
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding PKCS7 per allineare i dati alla dimensione del blocco
	blockSize := block.BlockSize()
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, len(data)+padding)
	copy(padText, data)
	for i := len(data); i < len(padText); i++ {
		padText[i] = byte(padding)
	}

	// Cripta i dati in modalità CBC
	encryptedData := make([]byte, len(padText))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, padText)

	return encryptedData, iv, aesKey, nil
}