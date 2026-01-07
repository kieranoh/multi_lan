package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData şifreleme işlemi için AES ve CBC modunu kullanır.
// Verilen anahtar baytları yeterince uzun (>= 16 bayt) olmalıdır.
// Gerekli uzunluğa uyan verilen anahtar baytlarının ön ekini kullanır.
// Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürür.
// Arguments:
// - key: Şifreleme anahtarını oluşturmak için baytlar (en az 16 bayt).
// - data: Şifrelenecek veri.
// Returns:
// - (encryptedData, iv, aesKey): Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar.
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	if len(key) < 16 {
		return nil, nil, nil
	}

	// Anahtarın ilk 16 baytını kullan
	aesKey = key[:16]

	// IV oluştur (16 bayt uzunluğunda)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}

	// AES bloğu oluştur
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil
	}

	// Veriyi CBC moduna uygun hale getirme
	pad := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := append(data, byte(pad))
	for i := 1; i < pad; i++ {
		paddedData = append(paddedData, byte(pad))
	}

	// Şifreleme işlemi
	ciphertext := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(ciphertext, paddedData)

	return ciphertext, iv, aesKey
}