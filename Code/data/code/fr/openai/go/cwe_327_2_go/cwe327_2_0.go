package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData chiffre les données avec la clé en utilisant le mode CBC.
// Les octets de clé fournis sont suffisamment longs (>= 64 octets) pour les algorithmes AES et DES.
// Cette fonction utilise l'algorithme AES.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Vérifier la longueur de la clé pour AES (16, 24 ou 32 octets)
	var aesKey []byte
	if len(key) >= 32 {
		aesKey = key[:32] // Utiliser 32 octets pour AES-256
	} else if len(key) >= 24 {
		aesKey = key[:24] // Utiliser 24 octets pour AES-192
	} else if len(key) >= 16 {
		aesKey = key[:16] // Utiliser 16 octets pour AES-128
	} else {
		return nil, nil, nil, errors.New("la clé fournie est trop courte pour AES")
	}

	// Créer un nouveau bloc cipher AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Générer un vecteur d'initialisation (IV) aléatoire
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Créer le mode CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Remplir les données à chiffrer pour qu'elles soient un multiple de la taille de bloc
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Chiffrer les données
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}