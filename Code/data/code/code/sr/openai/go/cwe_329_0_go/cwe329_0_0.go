package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "io"
)

// encryptData enkriptujte podatke sa ključem koristeći AES i CBC mod.
// Vraća enkriptovane podatke, IV (inicijalizacioni vektor) i ključ korišćen za enkripciju.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
    // Proverava da li je ključ dovoljno dugačak
    if len(key) < 16 {
        return nil, nil, nil, errors.New("ključ mora biti najmanje 16 bajtova dug")
    }

    // Uzimanje prvih 16 bajtova ključa za AES
    aesKey = key[:16] 

    // Kreiranje novog AES blok ciphera
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Inicijalizacija IV
    iv = make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Kreiranje CBC mode enkriptora
    mode := cipher.NewCBCEncrypter(block, iv)

    // Padding podataka pre enkripcije
    padding := aes.BlockSize - len(data)%aes.BlockSize
    padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

    // Enkriptovanje podataka
    encryptedData = make([]byte, len(padtext))
    mode.CryptBlocks(encryptedData, padtext)

    return encryptedData, iv, aesKey, nil
}