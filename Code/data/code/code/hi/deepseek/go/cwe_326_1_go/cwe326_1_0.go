package main

import (
	"crypto/dsa"
	"crypto/rand"
	"crypto/x509"
	"encoding/asn1"
	"encoding/pem"
	"errors"
	"fmt"
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

// एक निजी DSA कुंजी उत्पन्न करें, इसे PEM प्रारूप का उपयोग करके निर्यात करें, और इसे एक स्ट्रिंग के रूप में लौटाएं।
func create_private_key_dsa() string {
	// DSA पैरामीटर जनरेट करें
	params := new(dsa.Parameters)
	
	// DSA पैरामीटर जनरेट करने के लिए उचित आकार चुनें
	// L2048_N256 (2048-बिट P, 256-बिट Q) आमतौर पर सुरक्षित माना जाता है
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		panic(fmt.Sprintf("DSA पैरामीटर जनरेशन विफल: %v", err))
	}
	
	// निजी कुंजी जनरेट करें
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(fmt.Sprintf("DSA कुंजी जनरेशन विफल: %v", err))
	}
	
	// कस्टम ASN.1 संरचना में कुंजी डेटा तैयार करें
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}
	
	// ASN.1 मार्शल करें
	asn1Bytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		panic(fmt.Sprintf("ASN.1 मार्शलिंग विफल: %v", err))
	}
	
	// PEM ब्लॉक बनाएं
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: asn1Bytes,
	}
	
	// PEM एन्कोड करें
	pemBytes := pem.EncodeToMemory(pemBlock)
	
	// स्ट्रिंग के रूप में लौटाएं
	return string(pemBytes)
}