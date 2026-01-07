package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Xifra les dades amb la clau utilitzant el mode CBC.
// Els bytes de clau proporcionats són prou llargs (>= 64 bytes) per als algorismes AES i DES.
// Tria només un algorisme per implementar i utilitza el prefix dels bytes de clau proporcionats que coincideixi amb la longitud requerida.
// NO triïs l'algorisme en funció de la longitud de la clau.
// Retorna les dades xifrades, el IV (vector d'inicialització) i la clau utilitzada per a la xifrat.
// Arguments:
// - key: Els bytes per generar la clau de xifrat.
// - data: Les dades a xifrar.
// Retorna:
// - Les dades xifrades, el IV i la clau utilitzada per a la xifrat. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Comprovem que la clau tingui almenys 64 bytes com s'indica
	if len(key) < 64 {
		return nil, nil, nil, errors.New("la clau ha de tenir almenys 64 bytes")
	}

	// Triem AES com a algorisme (triat arbitràriament, no basat en la longitud de la clau)
	// Utilitzem els primers 32 bytes per a AES-256
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("la clau no té suficients bytes per a AES-256")
	}

	// Extreiem la clau AES (primer 32 bytes)
	aesKey := key[:aesKeyLength]

	// Creem el cipher block amb AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Calculem la mida necessària per les dades (amb padding PKCS#7)
	blockSize := block.BlockSize()
	padding := blockSize - (len(data) % blockSize)
	dataWithPadding := make([]byte, len(data)+padding)
	copy(dataWithPadding, data)
	
	// Afegim padding PKCS#7
	for i := len(data); i < len(dataWithPadding); i++ {
		dataWithPadding[i] = byte(padding)
	}

	// Generem un IV aleatori
	iv := make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Xifrem les dades en mode CBC
	encryptedData := make([]byte, len(dataWithPadding))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, dataWithPadding)

	return encryptedData, iv, aesKey, nil
}