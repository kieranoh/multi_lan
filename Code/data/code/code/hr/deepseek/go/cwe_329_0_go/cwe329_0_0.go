import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// Odredimo potrebnu duljinu AES ključa (16, 24 ili 32 bajta za AES-128, AES-192, AES-256)
	keyLength := 32 // Koristimo AES-256 kao default
	
	// Provjerimo je li dostavljeni ključ dovoljno dug
	if len(key) < keyLength {
		// Ako nije, možemo koristiti padding ili vratiti grešku
		// Prema specifikaciji, ključ je uvijek >= 64 bajtova, pa ovo ne bi trebalo biti potrebno
		panic("Key is too short")
	}
	
	// Uzmemo prefiks dostavljenog ključa za AES ključ
	aesKey = key[:keyLength]
	
	// Kreiraj AES cipher blok
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}
	
	// Generiraj IV (inicijalizacijski vektor)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}
	
	// Pripremi podatke za šifriranje (PKCS7 padding)
	paddedData := pkcs7Pad(data, aes.BlockSize)
	
	// Kreiraj CBC šifriranje
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// Šifriraj podatke
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}

// PKCS7 padding funkcija
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}