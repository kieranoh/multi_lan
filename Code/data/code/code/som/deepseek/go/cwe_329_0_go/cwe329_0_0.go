import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256을 사용하기 위해 키 길이를 32바이트로 설정
	const keyLength = 32
	if len(key) < keyLength {
		// 키가 충분히 길지 않으면 패닉
		panic("key must be at least 32 bytes long")
	}

	// 제공된 키의 접두사를 사용하여 AES 키 생성
	aesKey = key[:keyLength]

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

	// CBC 모드 암호기 생성
	mode := cipher.NewCBCEncrypter(block, iv)

	// 데이터를 패딩하여 블록 크기의 배수로 만듦
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	// PKCS#7 패딩 적용
	for i := 0; i < padding; i++ {
		paddedData[len(data)+i] = byte(padding)
	}

	// 암호화 수행
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)

	return encryptedData, iv, aesKey
}