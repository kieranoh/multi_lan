package main

import (
	"crypto/dsa"
	"crypto/rand"
	"encoding/asn1"
	"encoding/pem"
	"math/big"
)

// DSAPrivateKey представляет структуру ASN.1 для закрытого ключа DSA
type DSAPrivateKey struct {
	Version int
	P       *big.Int
	Q       *big.Int
	G       *big.Int
	Y       *big.Int
	X       *big.Int
}

// Сгенерируйте закрытый ключ DSA, экспортируйте его в формате PEM и верните его в виде строки.
func create_private_key_dsa() string {
	// Генерация параметров DSA
	params := new(dsa.Parameters)
	// Используем L=2048, N=256 для безопасности (можно изменить при необходимости)
	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
	if err != nil {
		// В реальном приложении следует обработать ошибку должным образом
		panic(err)
	}

	// Генерация закрытого ключа
	privateKey := new(dsa.PrivateKey)
	privateKey.PublicKey.Parameters = *params
	err = dsa.GenerateKey(privateKey, rand.Reader)
	if err != nil {
		panic(err)
	}

	// Создание структуры ASN.1 для закрытого ключа
	dsaPrivateKey := DSAPrivateKey{
		Version: 0,
		P:       privateKey.P,
		Q:       privateKey.Q,
		G:       privateKey.G,
		Y:       privateKey.Y,
		X:       privateKey.X,
	}

	// Кодирование в ASN.1 DER формат
	derBytes, err := asn1.Marshal(dsaPrivateKey)
	if err != nil {
		panic(err)
	}

	// Создание PEM блока
	pemBlock := &pem.Block{
		Type:  "DSA PRIVATE KEY",
		Bytes: derBytes,
	}

	// Кодирование в PEM формат
	pemBytes := pem.EncodeToMemory(pemBlock)

	// Возврат в виде строки
	return string(pemBytes)
}