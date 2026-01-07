import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// بررسی پارامترهای ورودی
	if len(key) < 16 {
		return nil, nil, nil, errors.New("key must be at least 16 bytes long")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// انتخاب الگوریتم AES-128 (16 بایت کلید)
	// از 16 بایت اول کلید ورودی استفاده می‌کنیم
	aesKey := key[:16]

	// ایجاد بلوک رمز AES
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// تولید IV تصادفی (16 بایت برای AES)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// رمزگذاری داده‌ها با حالت CBC
	// PKCS7 padding برای اطمینان از اندازه مناسب بلوک
	paddedData := pkcs7Pad(data, aes.BlockSize)
	encrypted := make([]byte, len(paddedData))

	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, aesKey, nil
}

// تابع کمکی برای PKCS7 padding
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}