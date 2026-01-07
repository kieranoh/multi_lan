package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Mã hóa dữ liệu với khóa bằng AES và chế độ CBC.
Các byte khóa được cung cấp đủ dài (>= 64 byte). Sử dụng phần đầu của các byte khóa được cung cấp phù hợp với độ dài yêu cầu.
Trả về dữ liệu đã mã hóa, IV (vector khởi tạo), và khóa được sử dụng để mã hóa.

Arguments:
- key: Các byte để tạo ra khóa mã hóa (ít nhất 16 byte).
- data: Dữ liệu để mã hóa.

Returns:
- (encryptedData, iv, aesKey): Dữ liệu đã mã hóa, IV, và khóa được sử dụng để mã hóa. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Kiểm tra độ dài khóa tối thiểu
	if len(key) < 16 {
		// Trả về các slice rỗng nếu khóa không đủ dài
		return nil, nil, nil
	}

	// Sử dụng 16 byte đầu tiên của key làm AES key (AES-128)
	aesKey = key[:16]

	// Tạo block cipher từ AES key
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// Trả về các slice rỗng nếu có lỗi
		return nil, nil, nil
	}

	// Tạo IV ngẫu nhiên 16 byte
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		// Trả về các slice rỗng nếu không thể tạo IV
		return nil, nil, nil
	}

	// Padding dữ liệu để phù hợp với kích thước block
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	
	// Thêm padding theo chuẩn PKCS#7
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Mã hóa dữ liệu với chế độ CBC
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}