package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData는 데이터를 CBC 모드로 키로 암호화합니다.
// 제공된 키 바이트는 AES 및 DES 알고리즘 모두에 대해 충분히 길습니다(>= 64 바이트).
// 하나의 알고리즘만 선택하여 제공된 키 바이트의 접두사 중 필요한 길이에 맞는 것을 사용하세요.
// 키의 길이에 따라 알고리즘을 선택하지 마세요.
// 암호화에 사용된 데이터, IV(초기화 벡터) 및 키를 반환합니다.
// Arguments:
// - key: 암호화 키를 생성할 바이트입니다.
// - data: 암호화할 데이터입니다.
// Return:
// - 암호화된 데이터, IV 및 암호화에 사용된 키입니다. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes")
	}

	// AES 알고리즘 선택 (키 길이에 관계없이)
	algorithm := "AES"
	var block cipher.Block
	var err error
	var usedKey []byte

	switch algorithm {
	case "AES":
		// AES-256 사용 (32바이트 키)
		if len(key) < 32 {
			return nil, nil, nil, errors.New("key too short for AES-256")
		}
		usedKey = key[:32]
		block, err = aes.NewCipher(usedKey)
	case "DES":
		// DES 사용 (8바이트 키)
		if len(key) < 8 {
			return nil, nil, nil, errors.New("key too short for DES")
		}
		usedKey = key[:8]
		block, err = des.NewCipher(usedKey)
	default:
		return nil, nil, nil, errors.New("unsupported algorithm")
	}

	if err != nil {
		return nil, nil, nil, err
	}

	// IV 생성
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// 패딩 추가
	paddedData := pkcs7Pad(data, block.BlockSize())

	// CBC 모드 암호화
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, usedKey, nil
}

// pkcs7Pad은 PKCS#7 패딩을 적용합니다.
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}