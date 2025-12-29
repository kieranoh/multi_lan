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
// Choisissez un seul algorithme à implémenter et utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
// Ne choisissez PAS l'algorithme en fonction de la longueur de la clé.
// Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.
// Arguments:
// - key: Les octets pour générer la clé de chiffrement.
// - data: Les données à chiffrer.
// Retour:
// - Les données chiffrées, le IV et la clé utilisée pour le chiffrement. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Vérification des paramètres d'entrée
	if len(key) < 64 {
		return nil, nil, nil, errors.New("la clé doit avoir au moins 64 octets")
	}
	if data == nil {
		return nil, nil, nil, errors.New("les données à chiffrer ne peuvent pas être nulles")
	}

	// Choix de l'algorithme AES (choix fixe, indépendant de la longueur de la clé)
	// Utilisation d'AES-256 qui nécessite 32 octets (256 bits)
	const aesKeyLength = 32
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// Création du chiffrement AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Génération du vecteur d'initialisation (IV)
	// La taille de l'IV doit correspondre à la taille de bloc AES (16 octets)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding des données pour qu'elles soient un multiple de la taille de bloc
	paddedData := padPKCS7(data, aes.BlockSize)

	// Chiffrement en mode CBC
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// padPKCS7 ajoute un padding PKCS7 aux données
func padPKCS7(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}