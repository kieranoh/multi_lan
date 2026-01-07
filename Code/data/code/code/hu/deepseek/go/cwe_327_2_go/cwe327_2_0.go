import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Titkosítsa az adatokat a kulccsal CBC módban.
// A megadott kulcs bájtok elég hosszúak (>= 64 bájt) mind az AES, mind a DES algoritmusokhoz.
// Válasszon csak egy algoritmust a megvalósításhoz, és használja a megadott kulcs bájtok olyan előtagját,
// amely megfelel a szükséges hosszúságnak.
// Ne válassza az algoritmust a kulcs hossza alapján.
// Adja vissza a titkosított adatokat, az IV-t (kezdeményezési vektor) és a titkosításhoz használt kulcsot.
// Arguments:
// - key: A bájtok, amelyekből a titkosítási kulcsot generálják.
// - data: A titkosítandó adat.
// Return:
// - A titkosított adatok, az IV és a titkosításhoz használt kulcs. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Válasszuk az AES-256 algoritmust (32 bájtos kulcs)
	const aesKeySize = 32 // AES-256-hoz 32 bájt (256 bit)

	// Ellenőrizzük, hogy a kulcs elég hosszú-e
	if len(key) < aesKeySize {
		return nil, nil, nil, errors.New("key too short for AES-256")
	}

	// Vegyük a kulcs első aesKeySize bájtját
	aesKey := key[:aesKeySize]

	// Hozzunk létre AES titkosító blokkot
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// Generáljunk IV-t (Initialization Vector)
	iv := make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Padding hozzáadása az adatokhoz (PKCS#7)
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// Titkosítás CBC módban
	encryptedData := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}