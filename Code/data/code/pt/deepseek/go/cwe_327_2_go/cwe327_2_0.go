package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData criptografa os dados com a chave usando o modo CBC.
// Os bytes da chave fornecida são longos o suficiente (>= 64 bytes) para os algoritmos AES e DES.
// Escolhe apenas um algoritmo para implementar (AES) e usa o prefixo dos bytes da chave fornecida
// que corresponda ao comprimento necessário.
// Retorna os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Verifica se a chave fornecida tem pelo menos 64 bytes
	if len(key) < 64 {
		return nil, nil, nil, errors.New("a chave deve ter pelo menos 64 bytes")
	}

	// Escolhe o algoritmo AES (128 bits = 16 bytes)
	// Usa os primeiros 16 bytes da chave fornecida
	aesKey := key[:16]

	// Cria o bloco de cifra AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Cria o IV (vetor de inicialização)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Preenche os dados para que o comprimento seja múltiplo do tamanho do bloco
	paddedData := padData(data, aes.BlockSize)

	// Criptografa os dados no modo CBC
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padData preenche os dados usando o esquema PKCS#7
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}