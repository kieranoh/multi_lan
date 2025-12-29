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
// Arguments:
// - key: Los bytes para generar la clave de cifrado.
// - data: Los datos a cifrar.
// Return:
// - Los datos cifrados, el IV y la clave utilizada para la cifrado. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Elegir AES como algoritmo (128-bit, 192-bit o 256-bit)
	// Usaremos AES-256 que requiere 32 bytes de clave
	const aesKeyLength = 32

	// Verificar que la clave proporcionada tenga al menos la longitud requerida
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("la clave proporcionada es demasiado corta para AES-256")
	}

	// Tomar los primeros aesKeyLength bytes de la clave proporcionada
	aesKey := key[:aesKeyLength]

	// Crear el cifrador AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Crear el IV (vector de inicialización)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Añadir padding PKCS7 a los datos
	paddedData := addPKCS7Padding(data, aes.BlockSize)

	// Crear el cifrador en modo CBC
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// addPKCS7Padding añade padding PKCS7 a los datos
func addPKCS7Padding(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}