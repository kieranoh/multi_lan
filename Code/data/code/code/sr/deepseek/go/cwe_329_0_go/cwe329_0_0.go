import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Koristimo prvih 16 bajtova ključa za AES-128
	// (možete promeniti na 24 ili 32 bajta za AES-192 ili AES-256)
	keyLength := 16
	if len(key) < keyLength {
		// Ako ključ nije dovoljno dug, možemo proširiti ili vratiti grešku
		// Po specifikaciji, ključ je >= 64 bajta, ali dodajemo zaštitu
		panic("key is too short")
	}
	aesKey = key[:keyLength]

	// Kreiramo AES šifru
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// Kreiramo IV (inicijalizacioni vektor)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// Kreiramo CBC enkriptor
	mode := cipher.NewCBCEncrypter(block, iv)

	// Podaci moraju biti poravnati na dužinu bloka
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	// Dodajemo PKCS#7 padding
	for i := 0; i < padding; i++ {
		paddedData[len(data)+i] = byte(padding)
	}

	// Enkriptujemo podatke
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}