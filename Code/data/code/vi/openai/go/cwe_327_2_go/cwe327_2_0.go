package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "fmt"
    "io"
)

// encryptData mã hóa dữ liệu với khóa sử dụng chế độ CBC.
// Các byte khóa được cung cấp đủ dài (>= 64 byte) cho cả hai thuật toán AES và DES.
// Chọn chỉ một thuật toán để triển khai và sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
// KHÔNG chọn thuật toán dựa trên độ dài của khóa.
// Trả về dữ liệu đã mã hóa, IV (vector khởi tạo) và khóa được sử dụng để mã hóa.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Chọn thuật toán AES và tạo khóa 16 byte từ đầu vào
    aesKey := key[:16]

    // Tạo IV cho chế độ CBC
    iv := make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Khởi tạo cipher.Block
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Đệm dữ liệu để chắc chắn nó có kích thước hợp lệ cho chế độ CBC
    padding := aes.BlockSize - len(data)%aes.BlockSize
    paddedData := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

    // Mã hóa dữ liệu
    encryptedData := make([]byte, len(paddedData))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}