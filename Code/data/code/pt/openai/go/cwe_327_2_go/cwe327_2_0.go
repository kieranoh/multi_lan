package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData criptografa os dados com a chave usando o modo CBC.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Verifica se a chave é longa o suficiente para o AES
	if len(key) < 32 { // AES-256 requer uma chave de 32 bytes
		return nil, nil, nil, errors.New("chave insuficiente para AES-256")
	}

	// Usar os primeiros 32 bytes da chave para AES
	aesKey := key[:32]

	// Cria um bloco AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Gera um IV aleatório
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Cria um novo modo de bloco CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Criptografa os dados
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}