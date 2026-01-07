package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
// 제공된 키 바이트는 충분히 길어야 합니다 (>= 16 바이트).
// 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
// 암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.
//
// Arguments:
// - key: 암호화 키를 생성할 바이트 (최소 16 바이트).
// - data: 암호화할 데이터.
//
// Returns:
// - (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("키는 최소 16 바이트여야 합니다.")
	}

	// AES 키의 길이를 16 바이트로 조정합니다.
	aesKey = key[:16]

	// 초기화 벡터를 생성합니다.
	iv = make([]byte, aes.BlockSize)
	if _, err = io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// AES 블록 암호를 생성합니다.
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 패딩을 추가하여 데이터의 길이를 블록 크기의 배수로 만듭니다.
	data = pad(data, aes.BlockSize)

	// CBC 모드의 암호화기를 생성합니다.
	mode := cipher.NewCBCEncrypter(block, iv)

	// 암호화된 데이터를 저장할 슬라이스를 생성합니다.
	encryptedData = make([]byte, len(data))

	// 데이터를 암호화합니다.
	mode.CryptBlocks(encryptedData, data)

	return encryptedData, iv, aesKey, nil
}

// pad는 데이터를 주어진 블록 크기로 패딩합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}