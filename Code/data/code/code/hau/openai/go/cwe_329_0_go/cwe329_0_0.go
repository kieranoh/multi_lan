package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData는 AES 및 CBC 모드를 사용하여 제공된 키로 데이터를 암호화합니다.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	// 키의 길이를 확인하고 최소 16 바이트인지 확인합니다.
	if len(key) < 16 {
		return nil, nil, nil, errors.New("키는 최소 16 바이트여야 합니다")
	}

	// AES 암호화 키의 길이를 32 바이트로 맞추기 위해 제공된 키에서 접두사를 사용합니다.
	aesKey = key[:32] // 32 바이트 키를 사용하여 AES-256을 위한 키 생성

	// IV 생성
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// 패딩을 추가하여 AES 블록 크기에 맞춥니다.
	paddedData := pad(data, aes.BlockSize)

	// CBC 모드로 암호화
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	// 암호화된 데이터 반환
	return ciphertext, iv, aesKey, nil
}

// pad는 데이터를 AES 블록 크기에 맞추기 위해 PKCS#7 패딩을 추가합니다.
func pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(data, padText...)
}

func main() {
	// 사용 예시
}