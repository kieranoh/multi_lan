import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Provera da li su ulazni podaci validni
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}
	if data == nil {
		return nil, nil, nil, errors.New("data cannot be nil")
	}

	// Biramo AES-256 algoritam (32 bajta = 256 bita)
	const aesKeyLength = 32
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// Kreiranje AES blok šifre
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generisanje IV (inicijalizacionog vektora)
	// IV mora biti iste dužine kao blok (16 bajta za AES)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Kreiranje CBC enkriptora
	mode := cipher.NewCBCEncrypter(block, iv)

	// Podaci moraju biti poravnati na dužinu bloka
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	
	// Dodavanje PKCS#7 paddinga
	for i := 0; i < padding; i++ {
		paddedData[len(data)+i] = byte(padding)
	}

	// Enkripcija podataka
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}