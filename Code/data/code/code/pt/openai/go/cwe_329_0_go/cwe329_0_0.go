package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"fmt"
	"io"
)

// encryptData criptografa os dados com a chave usando AES e modo CBC.
// Os bytes da chave fornecida são longos o suficiente (>= 64 bytes).
// Use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário.
// Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Definindo o tamanho da chave AES (16 bytes para AES-128)
	keySize := 16
	if len(key) < keySize {
		return nil, nil, nil // chave inválida
	}
	aesKey = key[:keySize]

	// Criando um IV com 16 bytes
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil // erro ao gerar IV
	}

	// Criando o bloco AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil // erro ao criar bloco AES
	}

	// Padding dos dados para ser múltiplo do tamanho do bloco
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, byte(padding))
	for i := 1; i < padding; i++ {
		paddedData = append(paddedData, byte(padding))
	}

	// Criptografando os dados
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey
}