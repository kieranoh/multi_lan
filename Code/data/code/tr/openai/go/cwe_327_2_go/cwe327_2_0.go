package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"encoding/hex"
	"errors"
	"io"
)

// encryptData şifreleme işlemini gerçekleştirmek için CBC modunu kullanır.
// Sağlanan anahtar baytları, hem AES hem de DES algoritmaları için yeterince uzundur (>= 64 bayt).
// Sadece bir algoritma seçilir ve gereken uzunluğa uyan sağlanan anahtar baytlarının ön eki kullanılır.
// Anahtarın uzunluğuna göre algoritmayı seçmez. 
// Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürür.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 16 {
		return nil, nil, nil, errors.New("anahtarın uzunluğu en az 16 bayt olmalıdır (AES için)")
	}

	// AES algoritması kullanıyoruz
	aesKey := key[:16] // İlk 16 baytı kullanıyoruz
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// IV oluştur
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Veriyi şifrele
	padding := aes.BlockSize - len(data)%aes.BlockSize
	padtext := append(data, bytes.Repeat([]byte{byte(padding)}, padding)...)

	ciphertext := make([]byte, len(padtext))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, padtext)

	return ciphertext, iv, aesKey, nil
}