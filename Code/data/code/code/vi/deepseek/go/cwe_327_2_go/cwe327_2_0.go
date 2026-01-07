package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData mã hóa dữ liệu với khóa sử dụng chế độ CBC.
// Các byte khóa được cung cấp đủ dài (>= 64 byte) cho cả hai thuật toán AES và DES.
// Chọn chỉ một thuật toán để triển khai và sử dụng phần đầu của các byte khóa được cung cấp
// phù hợp với độ dài yêu cầu.
// KHÔNG chọn thuật toán dựa trên độ dài của khóa.
// Trả về dữ liệu đã mã hóa, IV (vector khởi tạo) và khóa được sử dụng để mã hóa.
// Arguments:
// - key: Các byte để tạo ra khóa mã hóa.
// - data: Dữ liệu để mã hóa.
// Return:
// - Dữ liệu đã mã hóa, IV và khóa được sử dụng để mã hóa. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Kiểm tra đầu vào
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	if data == nil {
		return nil, nil, nil, errors.New("data cannot be nil")
	}

	// Chọn thuật toán AES (chọn cố định, không dựa trên độ dài khóa)
	// Sử dụng AES-256 yêu cầu 32 byte khóa
	const aesKeySize = 32
	aesKey := make([]byte, aesKeySize)
	
	// Lấy phần đầu của key đủ cho AES-256
	copy(aesKey, key[:aesKeySize])

	// Tạo block cipher từ khóa AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Tạo IV (Initialization Vector)
	// Kích thước IV bằng với kích thước block của AES (16 byte)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding dữ liệu để phù hợp với kích thước block
	paddedData := pkcs7Pad(data, aes.BlockSize)

	// Tạo ciphertext
	ciphertext := make([]byte, len(paddedData))

	// Tạo encryptor với chế độ CBC
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey, nil
}

// pkcs7Pad thêm padding PKCS7 vào dữ liệu
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}