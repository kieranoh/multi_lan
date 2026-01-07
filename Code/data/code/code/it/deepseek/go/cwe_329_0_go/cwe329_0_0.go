package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Cripta i dati con la chiave utilizzando AES e modalità CBC.
I byte della chiave fornita sono abbastanza lunghi (>= 64 byte). Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
Restituisci i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.

Arguments:
- key: I byte per generare la chiave di crittografia (almeno 16 byte).
- data: I dati da crittografare.

Returns:
- (encryptedData, iv, aesKey): I dati crittografati, l'IV e la chiave utilizzata per la crittografia. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Determina la lunghezza della chiave AES (16, 24 o 32 byte per AES-128, AES-192, AES-256)
	keyLength := 32 // Usa AES-256 per default
	if len(key) < keyLength {
		// Se la chiave fornita è più corta, usa la massima lunghezza disponibile
		// tra 16, 24 o 32 byte
		if len(key) >= 32 {
			keyLength = 32
		} else if len(key) >= 24 {
			keyLength = 24
		} else if len(key) >= 16 {
			keyLength = 16
		} else {
			// Se la chiave è troppo corta, restituisci slice vuote
			return nil, nil, nil
		}
	}

	// Prendi il prefisso della chiave della lunghezza appropriata
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])

	// Crea il cifrario AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// Genera un IV casuale
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Aggiungi padding PKCS#7 ai dati
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Cripta i dati
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}