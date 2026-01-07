package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData cifra los datos con la clave usando AES y modo CBC.
// Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes).
// Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
// Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("la clave debe tener al menos 16 bytes")
	}

	// Usar los primeros 16 bytes de la clave como clave AES
	aesKey = key[:16]

	// Crear un nuevo bloque AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Crear un IV aleatorio
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding de datos
	paddedData := pad(data, aes.BlockSize)

	// Crear un nuevo bloque en modo CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Cifrar los datos
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pad agrega relleno a los datos para que sean un múltiplo del tamaño del bloque
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}