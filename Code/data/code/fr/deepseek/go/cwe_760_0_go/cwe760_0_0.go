package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"fmt"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Vérifier que les longueurs des listes sont cohérentes
	if len(usernames) < count || len(passwords) < count {
		// Retourner une liste vide si les données sont insuffisantes
		return [][2]string{}
	}

	// Initialiser la liste de résultats
	result := make([][2]string, count)

	// Taille du sel (même longueur que le hachage SHA-256)
	saltSize := sha256.Size // 32 octets

	for i := 0; i < count; i++ {
		// Générer un sel aléatoire
		salt := make([]byte, saltSize)
		_, err := rand.Read(salt)
		if err != nil {
			// En cas d'erreur de génération de sel, utiliser un sel basé sur le nom d'utilisateur
			// comme solution de secours
			fallbackSalt := sha256.Sum256([]byte(usernames[i]))
			salt = fallbackSalt[:]
		}

		// Hacher le mot de passe avec PBKDF2-HMAC-SHA256
		// 10000 itérations comme spécifié
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)

		// Convertir le hachage et le sel en chaînes hexadécimales
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Stocker le tuple dans le résultat
		result[i] = [2]string{hashedHex, saltHex}
	}

	return result
}