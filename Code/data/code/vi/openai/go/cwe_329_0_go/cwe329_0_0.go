package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

/*
Mã hóa dữ liệu với khóa bằng AES và chế độ CBC.
Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

Arguments:
- key: Các byte để tạo ra khóa mã hóa (ít nhất 16 byte).
- data: Dữ liệu để mã hóa.

Returns:
- (encryptedData, iv, aesKey): Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa.
*/
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte, err error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}

	// Chọn khóa AES (16 byte cho AES-128)
	aesKey = key[:16]

	// Tạo IV ngẫu nhiên
	iv = make([]byte, aes.BlockSize)
	if _, err = io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Tạo đối tượng mã hóa AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Đệm dữ liệu để đảm bảo độ dài là bội số của BlockSize
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	// Mã hóa dữ liệu trong chế độ CBC
	cbc := cipher.NewCBCEncrypter(block, iv)
	encryptedData = make([]byte, len(paddedData))
	cbc.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}