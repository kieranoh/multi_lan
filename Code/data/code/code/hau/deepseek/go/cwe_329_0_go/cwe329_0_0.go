func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
    // 필요한 AES 키 길이 (AES-256을 위해 32바이트)
    const aesKeyLength = 32
    
    // 키 길이 검증
    if len(key) < 16 {
        panic("키는 최소 16바이트 이상이어야 합니다")
    }
    
    // 제공된 키에서 필요한 길이만큼 접두사 사용
    if len(key) < aesKeyLength {
        // 키가 너무 짧으면 패딩 (실제 사용 시 더 안전한 키 파생 함수 사용 권장)
        aesKey = make([]byte, aesKeyLength)
        copy(aesKey, key)
        // 나머지 부분을 키 바이트로 채움
        for i := len(key); i < aesKeyLength; i++ {
            aesKey[i] = key[i%len(key)]
        }
    } else {
        // 충분히 길면 처음 32바이트 사용
        aesKey = key[:aesKeyLength]
    }
    
    // 블록 크기 (AES 블록 크기 = 16바이트)
    blockSize := 16
    
    // IV 생성 (랜덤 16바이트)
    iv = make([]byte, blockSize)
    _, err := rand.Read(iv)
    if err != nil {
        panic("IV 생성 실패: " + err.Error())
    }
    
    // AES 블록 생성
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        panic("AES 암호화 블록 생성 실패: " + err.Error())
    }
    
    // CBC 모드 암호기 생성
    mode := cipher.NewCBCEncrypter(block, iv)
    
    // PKCS#7 패딩 적용
    padding := blockSize - len(data)%blockSize
    paddedData := make([]byte, len(data)+padding)
    copy(paddedData, data)
    for i := len(data); i < len(paddedData); i++ {
        paddedData[i] = byte(padding)
    }
    
    // 암호화 수행
    encryptedData = make([]byte, len(paddedData))
    mode.CryptBlocks(encryptedData, paddedData)
    
    return encryptedData, iv, aesKey
}