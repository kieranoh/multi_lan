package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData cripta i dati con la chiave utilizzando la modalità CBC.
// I byte della chiave fornita sono abbastanza lunghi (>= 64 byte) per AES.
// Restituisce i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Assicurati che la chiave sia lunga almeno 16 byte per AES
	if len(key) < 16 {
		return nil, nil, nil, errors.New("la chiave deve essere lunga almeno 16 byte")
	}

	// Usa i primi 16 byte della chiave per la chiave AES
	aesKey := key[:16]

	// Crea un nuovo blocco AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Crea un IV (vector di inizializzazione) lungo 16 byte
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Crea il cipher CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Padding dei dati per la crittografia
	data = pad(data, aes.BlockSize)

	// Crittografa i dati
	encryptedData := make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad aggiunge padding ai dati secondo lo schema PKCS#7.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}