/* 데이터를 AES 및 CBC 모드를 사용하여 키로 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터) 및 암호화에 사용된 키를 반환합니다.

Arguments:
- key: 암호화 키를 생성할 바이트 (최소 16 바이트).
- data: 암호화할 데이터.

Returns:
- (encryptedData, iv, aesKey): 암호화된 데이터, IV 및 암호화에 사용된 키. */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
    // 키 길이 검증
    if len(key) < 16 {
        panic("키는 최소 16바이트 이상이어야 합니다")
    }
    
    // AES-256을 사용하기 위해 32바이트 키 생성
    // 제공된 키의 접두사 32바이트를 사용
    aesKey = key[:32]
    
    // 블록 크기 확인 (AES 블록 크기 = 16바이트)
    blockSize := 16
    
    // PKCS7 패딩 적용
    padding := blockSize - len(data)%blockSize
    padText := make([]byte, len(data)+padding)
    copy(padText, data)
    for i := len(data); i < len(padText); i++ {
        padText[i] = byte(padding)
    }
    
    // CBC 모드에서 사용할 IV 생성 (16바이트)
    iv = make([]byte, blockSize)
    _, err := rand.Read(iv)
    if err != nil {
        panic("IV 생성 실패: " + err.Error())
    }
    
    // AES 블록 생성
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        panic("AES 암호화 실패: " + err.Error())
    }
    
    // CBC 모드 암호화
    encryptedData = make([]byte, len(padText))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(encryptedData, padText)
    
    return encryptedData, iv, aesKey
}