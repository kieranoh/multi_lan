import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* 주어진 키를 사용하여 AES 및 CBC 모드로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

Arguments:
- key: 암호화 키를 생성할 바이트 (최소 16 바이트).
- data: 암호화할 데이터.

Returns:
- (encryptedData, iv, aesKey): 암호화된 데이터, IV, 및 암호화에 사용된 키. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES 키 길이 선택 (16, 24, 또는 32 바이트)
	keyLength := 32 // 기본적으로 256비트 키 사용
	if len(key) < keyLength {
		// 제공된 키가 충분히 길지 않으면 가능한 최대 길이 사용
		if len(key) >= 16 {
			keyLength = 16
		} else if len(key) >= 24 {
			keyLength = 24
		} else {
			// 키가 너무 짧으면 패딩 (실제 구현에서는 오류 반환 고려)
			paddedKey := make([]byte, 16)
			copy(paddedKey, key)
			aesKey = paddedKey
		}
	}
	
	if aesKey == nil {
		aesKey = key[:keyLength]
	}
	
	// AES 블록 생성
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		// 오류 발생 시 nil 반환
		return nil, nil, nil
	}
	
	// 데이터 패딩
	blockSize := block.BlockSize()
	padding := blockSize - len(data)%blockSize
	padText := make([]byte, len(data)+padding)
	copy(padText, data)
	for i := len(data); i < len(padText); i++ {
		padText[i] = byte(padding)
	}
	
	// IV 생성
	iv = make([]byte, blockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		return nil, nil, nil
	}
	
	// CBC 모드 암호화
	encryptedData = make([]byte, len(padText))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, padText)
	
	return encryptedData, iv, aesKey
}