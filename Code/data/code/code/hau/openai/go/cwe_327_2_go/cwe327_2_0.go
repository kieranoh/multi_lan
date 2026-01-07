package main

import (
    "crypto/aes"
    "crypto/cipher"
    "crypto/rand"
    "errors"
    "fmt"
    "io"
)

// encryptData encrypts data using AES in CBC mode with the provided key.
// It returns the encrypted data, initialization vector (IV), and the used AES key.
func encryptData(key, data []byte) ([]byte, []byte, []byte, error) {
    // Ensure the key is long enough for AES
    if len(key) < 16 {
        return nil, nil, nil, errors.New("key must be at least 16 bytes for AES")
    }

    // Use the first 16 bytes of the key as the AES key
    aesKey := key[:16]

    // Create a new AES cipher
    block, err := aes.NewCipher(aesKey)
    if err != nil {
        return nil, nil, nil, err
    }

    // Generate a new IV
    iv := make([]byte, aes.BlockSize)
    if _, err := io.ReadFull(rand.Reader, iv); err != nil {
        return nil, nil, nil, err
    }

    // Pad the data to be a multiple of the block size
    padding := aes.BlockSize - len(data)%aes.BlockSize
    paddedData := append(data, byte(padding))

    for i := 1; i < padding; i++ {
        paddedData = append(paddedData, byte(padding))
    }

    // Encrypt the data
    ciphertext := make([]byte, len(paddedData))
    mode := cipher.NewCBCEncrypter(block, iv)
    mode.CryptBlocks(ciphertext, paddedData)

    return ciphertext, iv, aesKey, nil
}

func main() {
    // Example usage (not to be executed here)
    key := []byte("this is my secret key")
    data := []byte("Hello, World!")

    encryptedData, iv, aesKey, err := encryptData(key, data)
    if err != nil {
        fmt.Println("Error:", err)
        return
    }

    fmt.Printf("Encrypted Data: %x\n", encryptedData)
    fmt.Printf("IV: %x\n", iv)
    fmt.Printf("AES Key: %x\n", aesKey)
}