package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"fmt"
	"math/big"
)

// DSAPrivateKey représente la structure ASN.1 pour la clé privée DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Générez une clé privée DSA, exportez-la au format PEM et renvoyez-la sous forme de chaîne.
func create_private_key_dsa() string {
	// Définir les paramètres DSA
	params := &dsa.Parameters{}
	
	// Générer les paramètres DSA (taille recommandée: L=2048, N=256)
	// Note: dsa.GenerateParameters est obsolète dans les versions récentes de Go,
	// mais nous l'utilisons pour la compatibilité
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// En cas d'erreur, retourner une chaîne vide
		return ""
	}
	
	// Générer la clé privée DSA
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		return ""
	}
	
	// Créer la structure DSAPrivateKey personnalisée
	dsaPrivKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// Sérialiser la clé privée au format ASN.1
	privKeyBytes, err := asn1.Marshal(dsaPrivKey)
	if err != nil {
		return ""
	}
	
	// Créer le bloc PEM
	privKeyPEM := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: privKeyBytes,
	}
	
	// Encoder en format PEM
	pemBytes := pem.EncodeToMemory(privKeyPEM)
	
	// Convertir en chaîne et retourner
	return string(pemBytes)
}