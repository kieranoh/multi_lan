import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256 használata, amihez 32 bájtos kulcs kell
	const aesKeyLength = 32
	
	// Ellenőrizzük, hogy a kulcs elég hosszú-e
	if len(key) < aesKeyLength {
		// Ha nem elég hosszú, kiegészítjük nullákkal
		paddedKey := make([]byte, aesKeyLength)
		copy(paddedKey, key)
		aesKey = paddedKey
	} else {
		// Csak az első 32 bájtot használjuk
		aesKey = key[:aesKeyLength]
	}
	
	// AES blokk titkosító létrehozása
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// Hiba esetén üres slice-ekkel térünk vissza
		return []byte{}, []byte{}, []byte{}
	}
	
	// PKCS7 padding hozzáadása az adatokhoz
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}
	
	// IV generálása (16 bájt, mert AES blokkméret 16 bájt)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return []byte{}, []byte{}, []byte{}
	}
	
	// CBC módú titkosító létrehozása
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// Titkosítás
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}