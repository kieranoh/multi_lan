package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "io"
)

// encryptData cripta i dati con la chiave utilizzando AES e modalità CBC.
// I byte della chiave fornita sono abbastanza lunghi (>= 64 byte).
// Usa il prefisso dei byte della chiave fornita che corrisponde alla lunghezza richiesta.
// Restituisce i dati crittografati, l'IV (vector di inizializzazione) e la chiave utilizzata per la crittografia.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
    // Controlla se la chiave è lunga almeno 16 byte
    if len(key) < 16 {
        return nil, nil, nil, errors.New("la chiave deve essere di almeno 16 byte")
    }

    // Truncate the key to 16 bytes for AES-128
    aesKey = key[:16]

    // Crea un nuovo blocco AES
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Inizializza l'IV
    iv = make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Padding dei dati
    padding := aes.BlockSize - len(data)%aes.BlockSize
    padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

    // Crittografia in modalità CBC
    encryptedData = make([]byte, len(padtext))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(encryptedData, padtext)

    return encryptedData, iv, aesKey, nil
}