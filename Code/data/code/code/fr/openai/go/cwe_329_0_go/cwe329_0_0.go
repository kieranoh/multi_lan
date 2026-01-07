package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData crypte les données avec la clé en utilisant AES et le mode CBC.
// Les octets de clé fournis sont suffisamment longs (>= 64 octets). 
// Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
// Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("la clé doit avoir au moins 16 octets")
	}

	// Générez une clé AES de 16, 24 ou 32 octets (AES-128, AES-192, AES-256)
	var aesKeyLength int
	switch len(key) {
	case 16:
		aesKeyLength = 16
	case 24:
		aesKeyLength = 24
	case 32:
		aesKeyLength = 32
	default:
		aesKeyLength = 16 // par défaut, utiliser 16 octets
	}

	// Extraire la clé AES à partir de la clé donnée
	aesKey = key[:aesKeyLength]

	// Créer un vecteur d'initialisation (IV)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Créer un nouveau cipher AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// S'assurer que les données à chiffrer sont un multiple de la taille du bloc
	data = pad(data, aes.BlockSize)

	// Créer un nouveau mode CBC
	mode := cipher.NewCBCEncrypter(block, iv)

	// Chiffrer les données
	encryptedData = make([]byte, len(data))
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad ajoute des octets de remplissage aux données pour qu'elles soient un multiple de blockSize
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padtext...)
}