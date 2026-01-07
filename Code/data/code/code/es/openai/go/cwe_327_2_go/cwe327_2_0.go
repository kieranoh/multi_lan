package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "io"
)

// encryptData cifra los datos con la clave utilizando el modo CBC.
// Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes) para los algoritmos AES y DES.
// Elige solo un algoritmo para implementar y utiliza el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
// NO elijas el algoritmo basado en la longitud de la clave.
// Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Usamos AES, por lo que la longitud de la clave debe ser 16, 24 o 32 bytes.
    aesKey := key[:32] // Tomamos los primeros 32 bytes para AES-256
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Creamos un IV aleatorio
    iv := make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Preparar el cifrador en modo CBC
    mode := cipher.NewCBCEncrypter(block, iv)

    // Aseguramos que los datos a cifrar tengan longitud adecuada
    padding := aes.BlockSize - len(data)%aes.BlockSize
    padtext := append(data, byte(padding))
    for i := 1; i < padding; i++ {
        padtext = append(padtext, byte(padding))
    }

    // Cifrar los datos
    encryptedData := make([]byte, len(padtext))
    mode.CryptBlocks(encryptedData, padtext)

    return encryptedData, iv, aesKey, nil
}