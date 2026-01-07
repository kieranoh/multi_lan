import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Use the first 32 bytes of the key for AES-256 (or first 16/24 for AES-128/192)
	keyLength := 32 // AES-256
	if len(key) < keyLength {
		// Fallback to AES-128 if key is too short (though spec says >= 64 bytes)
		keyLength = 16
	}
	aesKey = key[:keyLength]

	// Create the AES cipher
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// In production, you might want to handle this error differently
		panic(err)
	}

	// Generate a random IV
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Pad the data if necessary
	paddedData := padPKCS7(data, aes.BlockSize)

	// Create the CBC encryptor
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}

// padPKCS7 adds PKCS7 padding to the data
func padPKCS7(data []byte, blockSize int) []byte {
	padding := blockSize - (len(data) % blockSize)
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}