import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/des"
	"crypto/rand"
	"errors"
	"io"
)

// encryptData encrypts data in CBC mode using either AES or DES algorithm.
// The provided key bytes are long enough for both AES and DES algorithms (>= 64 bytes).
// Only one algorithm is selected using the prefix of the provided key bytes of required length.
// The algorithm is not selected based on the length of the key.
// Returns the encrypted data, IV (initialization vector), and the key used for encryption.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
	if len(key) < 64 {
		return nil, nil, nil, errors.New("key must be at least 64 bytes long")
	}

	if len(data) == 0 {
		return nil, nil, nil, errors.New("data cannot be empty")
	}

	// Choose AES algorithm (using first 32 bytes for AES-256)
	// You can modify this logic to choose DES instead if needed
	algorithmChoice := "AES" // Fixed choice for this implementation

	var block cipher.Block
	var err error
	var usedKey []byte

	switch algorithmChoice {
	case "AES":
		// Use first 32 bytes for AES-256
		if len(key) < 32 {
			return nil, nil, nil, errors.New("key too short for AES-256")
		}
		aesKey := key[:32]
		block, err = aes.NewCipher(aesKey)
		usedKey = aesKey
	case "DES":
		// Use first 8 bytes for DES
		if len(key) < 8 {
			return nil, nil, nil, errors.New("key too short for DES")
		}
		desKey := key[:8]
		block, err = des.NewCipher(desKey)
		usedKey = desKey
	default:
		return nil, nil, nil, errors.New("unsupported algorithm")
	}

	if err != nil {
		return nil, nil, nil, err
	}

	// Generate IV
	iv := make([]byte, block.BlockSize())
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil, err
	}

	// Pad data if necessary for block cipher
	paddedData := padData(data, block.BlockSize())

	// Encrypt in CBC mode
	encrypted := make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encrypted, paddedData)

	return encrypted, iv, usedKey, nil
}

// padData pads data to be multiple of blockSize using PKCS#7 padding
func padData(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}