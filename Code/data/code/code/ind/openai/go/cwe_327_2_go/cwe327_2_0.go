package main

import (
	"crypto/aes"
	"crypto/des"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 CBC 모드로 주어진 키로 데이터를 암호화합니다.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	var block cipher.Block
	var err error

	// 키가 AES 알고리즘에 적합한지 확인합니다.
	if len(key) >= 32 {
		// AES에 필요한 키 길이: 16(128비트), 24(192비트), 32(256비트)
		block, err = aes.NewCipher(key[:32]) // 32바이트를 사용하여 AES 키 생성
	} else if len(key) >= 8 {
		// DES에 필요한 키 길이: 8바이트
		block, err = des.NewCipher(key[:8]) // 8바이트를 사용하여 DES 키 생성
	} else {
		return nil, nil, nil, errors.New("키 길이가 너무 짧습니다.")
	}

	if err != nil {
		return nil, nil, nil, err
	}

	// IV(초기화 벡터)를 생성합니다.
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 암호화할 데이터를 블록 크기에 맞게 패딩합니다.
	paddedData := pad(data, block.BlockSize())

	// 암호화 작업을 수행합니다.
	mode := cipher.NewCBCEncrypter(block, iv)
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, key[:32], nil // AES 키를 반환합니다.
}

// pad는 데이터를 블록 크기에 맞게 패딩합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}