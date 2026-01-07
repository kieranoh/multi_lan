func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Validate input parameters
    if len(key) < 64 {
        return nil, nil, nil, fmt.Errorf("key must be at least 64 bytes long")
    }
    if len(data) == 0 {
        return nil, nil, nil, fmt.Errorf("data cannot be empty")
    }

    // Choose AES-256 algorithm (using first 32 bytes of key)
    // AES-256 requires 32-byte key
    aesKey := key[:32]
    
    // Generate random IV (16 bytes for AES block size)
    iv := make([]byte, aes.BlockSize)
    if _, err := rand.Read(iv); err != nil {
        return nil, nil, nil, fmt.Errorf("failed to generate IV: %v", err)
    }

    // Create cipher block
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, fmt.Errorf("failed to create cipher: %v", err)
    }

    // Pad data to be multiple of block size
    padLen := aes.BlockSize - (len(data) % aes.BlockSize)
    padding := bytes.Repeat([]byte{byte(padLen)}, padLen)
    paddedData := append(data, padding...)

    // Create CBC encrypter
    encryptedData := make([]byte, len(paddedData))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey, nil
}