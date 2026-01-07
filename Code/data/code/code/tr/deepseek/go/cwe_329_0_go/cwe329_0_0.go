package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* Verileri AES ve CBC modunu kullanarak anahtar ile şifreleyin. Verilen anahtar baytları yeterince uzun (>= 64 bayt). Gerekli uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın. Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

Arguments:
- key: Şifreleme anahtarını oluşturmak için baytlar (en az 16 bayt).
- data: Şifrelenecek veri.

Returns:
- (encryptedData, iv, aesKey): Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES anahtar uzunluğunu belirle (16, 24 veya 32 bayt)
	keyLength := 32 // 256-bit anahtar kullanıyoruz
	
	// Anahtarın yeterli uzunlukta olduğundan emin ol
	if len(key) < keyLength {
		// Anahtar çok kısa ise, güvenli olmayan bir şekilde doldur
		paddedKey := make([]byte, keyLength)
		copy(paddedKey, key)
		for i := len(key); i < keyLength; i++ {
			paddedKey[i] = byte(i % 256)
		}
		aesKey = paddedKey[:keyLength]
	} else {
		// Anahtar yeterince uzun, ilk keyLength baytını kullan
		aesKey = key[:keyLength]
	}
	
	// AES cipher oluştur
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// Hata durumunda boş dilimler döndür
		return nil, nil, nil
	}
	
	// IV oluştur (16 bayt - AES blok boyutu)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}
	
	// Veriyi PKCS7 padding ile doldur
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}
	
	// CBC modunda şifrele
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}