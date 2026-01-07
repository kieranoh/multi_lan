package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Cryptez les données avec la clé en utilisant AES et le mode CBC.
Les octets de clé fournis sont suffisamment longs (>= 64 octets). Utilisez le préfixe des octets de clé fournis qui correspond à la longueur requise.
Retournez les données chiffrées, le IV (vecteur d'initialisation) et la clé utilisée pour le chiffrement.

Arguments:
- key: Les octets pour générer la clé de chiffrement (au moins 16 octets).
- data: Les données à chiffrer.

Returns:
- (encryptedData, iv, aesKey): Les données chiffrées, le IV et la clé utilisée pour le chiffrement. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Vérifier que la clé a au moins 16 octets
	if len(key) < 16 {
		// Retourner des slices vides si la clé est trop courte
		return nil, nil, nil
	}

	// Utiliser les premiers 32 octets pour AES-256 (ou 16 pour AES-128, 24 pour AES-192)
	// Nous utiliserons AES-256 (32 octets) pour une sécurité maximale
	keyLength := 32
	if len(key) < keyLength {
		keyLength = 16 // Fallback sur AES-128 si pas assez d'octets
	}

	// Prendre le préfixe de la clé de la longueur appropriée
	aesKey = make([]byte, keyLength)
	copy(aesKey, key[:keyLength])

	// Créer un nouveau cipher avec la clé
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// En cas d'erreur, retourner des slices vides
		return nil, nil, nil
	}

	// Créer un IV (vecteur d'initialisation) aléatoire
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// Préparer les données pour le chiffrement (ajout du padding PKCS7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Chiffrer les données avec le mode CBC
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}