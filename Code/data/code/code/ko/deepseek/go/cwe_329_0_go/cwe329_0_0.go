import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

Arguments:
- key: 암호화 키를 생성할 바이트(최소 16 바이트).
- data: 암호화할 데이터.

Returns:
- (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256을 사용하기 위해 32바이트 키 생성
	const keyLength = 32
	if len(key) < keyLength {
		// 키가 충분히 길지 않으면 패닉
		panic("key must be at least 32 bytes for AES-256")
	}
	
	// 제공된 키의 접두사를 사용하여 AES 키 생성
	aesKey = key[:keyLength]
	
	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}
	
	// 블록 크기 확인
	blockSize := block.BlockSize()
	
	// PKCS7 패딩 적용
	paddedData := pkcs7Pad(data, blockSize)
	
	// IV 생성 (초기화 벡터)
	iv = make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}
	
	// CBC 모드 암호화기 생성
	mode := cipher.NewCBCEncrypter(block, iv)
	
	// 암호화 수행
	encryptedData = make([]byte, len(paddedData))
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}

// PKCS7 패딩 함수
func pkcs7Pad(data []byte, blockSize int) []byte {
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, padding)
	for i := range padText {
		padText[i] = byte(padding)
	}
	return append(data, padText...)
}