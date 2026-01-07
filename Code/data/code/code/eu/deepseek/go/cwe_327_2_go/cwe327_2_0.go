import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

// Datuak gakoa erabiliz CBC moduan enkriptatu.
// Emandako gako byteak nahikoa luzeak dira (>= 64 byte) AES eta DES algoritmoentzat.
// Aldagai bakar bat hautatu implementatzeko eta emandako gako byteen aurprefikua erabili behar duzu beharrezko luzera lortzeko.
// Ez hautatu algoritmoa gakoaren luzeraren arabera.
// Itzuli enkriptatutako datuak, IV (hasierako bideratzailea), eta enkriptatzeko erabilitako gakoa.
// Argumentuak:
// - gakoa: Enkriptatzeko gakoa sortzeko byteak.
// - datuak: Enkriptatu beharreko datuak.
// Itzuli:
// - Enkriptatutako datuak, IV, eta enkriptatzeko erabilitako gakoa. (encryptedData, iv, aesKey, error)
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	// Egiaztatu sarrerako parametroak
	if len(key) < 64 {
		return nil, nil, nil, errors.New("gakoa gutxienez 64 byte luze izan behar du")
	}
	if len(data) == 0 {
		return nil, nil, nil, errors.New("datuak hutsik ezin dira egon")
	}

	// AES algoritmoa hautatu (aldagai bakar bat)
	// AES-256 erabiltzeko 32 byteko gakoa behar dugu
	const aesKeyLength = 32
	if len(key) < aesKeyLength {
		return nil, nil, nil, errors.New("gakoa motzegia da AES-256 erabiltzeko")
	}

	// Gakoa sortu emandako gakoaren aurprefikoa erabiliz
	aesKey := make([]byte, aesKeyLength)
	copy(aesKey, key[:aesKeyLength])

	// AES bloke zifratzailea sortu
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		return nil, nil, nil, err
	}

	// PKCS7 padding aplikatu datuei
	paddedData := pkcs7Pad(data, block.BlockSize())

	// IV (Initialization Vector) sortu
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// CBC moduko enkriptatzailea sortu
	mode := cipher.NewCBCEncrypter(block, iv)

	// Datuak enkriptatu
	encryptedData := make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey, nil
}

// pkcs7Pad datuak betetzeko PKCS7 estandarra erabiltzen du
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}