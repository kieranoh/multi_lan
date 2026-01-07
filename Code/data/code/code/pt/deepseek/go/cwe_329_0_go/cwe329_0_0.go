package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Criptografe os dados com a chave usando AES e modo CBC.
Os bytes da chave fornecida são longos o suficiente (>= 64 bytes). Use o prefixo dos bytes da chave fornecida que corresponda ao comprimento necessário.
Retorne os dados criptografados, o IV (vetor de inicialização) e a chave usada para a criptografia.

Arguments:
- key: Os bytes para gerar a chave de criptografia (pelo menos 16 bytes).
- data: Os dados a serem criptografados.

Returns:
- (encryptedData, iv, aesKey): Os dados criptografados, o IV e a chave usada para a criptografia. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Usar os primeiros 32 bytes da chave fornecida para AES-256
	keyLength := 32
	if len(key) < keyLength {
		// Se a chave for menor que o necessário, preencher com zeros
		aesKey = make([]byte, keyLength)
		copy(aesKey, key)
	} else {
		aesKey = key[:keyLength]
	}

	// Criar o cifrador AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Gerar IV aleatório
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Preencher os dados para serem múltiplos do tamanho do bloco
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Criptografar os dados
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}