package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

// hashCertificate hache de manière sécurisée le certificat donné et retourne le hachage sous forme de chaîne hexadécimale.
// @param cert Le certificat à hacher.
// @return Le certificat haché de manière sécurisée sous forme de chaîne hexadécimale.
func hashCertificate(cert string) string {
	// Nettoyer le certificat en supprimant les espaces blancs superflus
	cleanedCert := strings.TrimSpace(cert)
	
	// Vérifier si le certificat est vide après nettoyage
	if cleanedCert == "" {
		// Retourner le hachage d'une chaîne vide pour maintenir la cohérence
		hash := sha256.Sum256([]byte(""))
		return hex.EncodeToString(hash[:])
	}
	
	// Calculer le hachage SHA-256 du certificat nettoyé
	hash := sha256.Sum256([]byte(cleanedCert))
	
	// Convertir le hachage en chaîne hexadécimale
	return hex.EncodeToString(hash[:])
}