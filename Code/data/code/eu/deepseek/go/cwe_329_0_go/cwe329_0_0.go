import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "io"
)

func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
    // AES-256 erabiltzeko 32 byteko gakoa behar dugu
    // Emandako gakoaren aurprefikoa erabiltzen dugu behar den luzera lortzeko
    keyLength := 32 // AES-256
    if len(key) < keyLength {
        // Gakoa laburregia bada, errepikatu behar den luzera lortzeko
        paddedKey := make([]byte, keyLength)
        for i := 0; i < keyLength; i++ {
            paddedKey[i] = key[i%len(key)]
        }
        aesKey = paddedKey
    } else {
        // Gakoa nahikoa luzea bada, aurprefikoa hartu
        aesKey = key[:keyLength]
    }

    // AES bloke zifratzailea sortu
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        panic(err) // Praktikan errore hobe bat maneiatu beharko litzateke
    }

    // CBC modurako IV (Initialization Vector) sortu
    iv = make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        panic(err)
    }

    // Datuak CBC moduan enkriptatu
    // Datuak padding-a aplikatu behar zaio AES bloke tamainara egokitzeko
    blockSize := block.BlockSize()
    paddedData := pkcs7Pad(data, blockSize)
    
    encryptedData = make([]byte, len(paddedData))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(encryptedData, paddedData)

    return encryptedData, iv, aesKey
}

// pkcs7Pad datuak padding-a aplikatzen ditu bloke tamainara egokitzeko
func pkcs7Pad(data []byte, blockSize int) []byte {
    padding := blockSize - len(data)%blockSize
    padText := make([]byte, len(data)+padding)
    copy(padText, data)
    for i := len(data); i < len(padText); i++ {
        padText[i] = byte(padding)
    }
    return padText
}