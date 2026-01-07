package main

import (
	"crypto/rand"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"fmt"
)

// Luo yksityinen RSA-avain, vie se PEM-muodossa ja palauta se merkkijonona.
func CreatePrivateKey() string {
	// Luo 2048-bittinen RSA-avain
	privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
	if err != nil {
		// Palauta tyhjä merkkijono virhetilanteessa
		return ""
	}

	// Muunna yksityinen avain DER-muotoon
	privateKeyDER := x509.MarshalPKCS1PrivateKey(privateKey)

	// Luo PEM-lohko
	privateKeyBlock := &pem.Block{
		Type:  "RSA PRIVATE KEY",
		Bytes: privateKeyDER,
	}

	// Koodaa PEM-muotoon
	privateKeyPEM := pem.EncodeToMemory(privateKeyBlock)

	// Muunna byte-taulukko merkkijonoksi ja palauta
	return string(privateKeyPEM)
}