import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"crypto/sha256"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// 키 길이 검증
	if len(key) < 16 {
		panic("키는 최소 16바이트 이상이어야 합니다")
	}

	// AES 키 생성 (SHA-256 해시 사용)
	hash := sha256.New()
	hash.Write(key[:64]) // 최대 64바이트까지 사용
	aesKey = hash.Sum(nil)[:32] // AES-256을 위한 32바이트 키

	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}

	// IV 생성 (16바이트)
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}

	// PKCS7 패딩
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}

	// CBC 모드 암호화
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}