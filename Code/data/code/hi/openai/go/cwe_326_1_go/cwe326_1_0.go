package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/pem"
	"errors"
	"math/big"
)

// DSAPrivateKey DSA निजी कुंजी के लिए ASN.1 संरचना का प्रतिनिधित्व करता है
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// create_private_key_dsa एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
func create_private_key_dsa() (string, error) {
	priv := new(dsa.PrivateKey)
	err := dsa.GenerateParameters(&priv.PublicKey, rand.Reader, dsa.L2048N256)
	if err != nil {
		return "", err
	}
	err = dsa.GenerateKey(priv, rand.Reader)
	if err != nil {
		return "", err
	}

	privBytes := x509.MarshalPKCS8PrivateKey(priv)
	pemBlock := &pem.Block{
		Type:  "PRIVATE KEY",
		Bytes: privBytes,
	}
	var pemData bytes.Buffer
	if err = pem.Encode(&pemData, pemBlock); err != nil {
		return "", err
	}

	return pemData.String(), nil
}