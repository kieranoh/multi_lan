package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// Verileri CBC modunu kullanarak anahtar ile şifreleyin.
// Sağlanan anahtar baytları, hem AES hem de DES algoritmaları için yeterince uzundur (>= 64 bayt).
// Sadece bir algoritma seçin ve gereken uzunluğa uyan sağlanan anahtar baytlarının ön ekini kullanın.
// Anahtarın uzunluğuna göre algoritmayı seçmeyin.
// Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.
// Arguments:
// - key: Şifreleme anahtarını oluşturmak için baytlar.
// - data: Şifrelenecek veri.
// Return:
// - Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Anahtar uzunluğunu kontrol et
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	// AES algoritmasını seçiyoruz (görev açıklamasında belirtildiği gibi)
	// AES-256 için 32 bayt anahtar kullanıyoruz
	const aesKeySize = 32
	aesKey := make([]byte, aesKeySize)
	copy(aesKey, key[:aesKeySize])

	// AES cipher bloğu oluştur
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Veriyi PKCS7 padding ile doldur
	paddedData := pkcs7Pad(data, block.BlockSize())

	// IV oluştur
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC modunda şifreleyici oluştur
	mode := cipher.NewCBCEncrypter(block, iv)

	// Şifrelenmiş veri için buffer oluştur
	encryptedData := make([]byte, len(paddedData))

	// Veriyi şifrele
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// PKCS7 padding uygula
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}