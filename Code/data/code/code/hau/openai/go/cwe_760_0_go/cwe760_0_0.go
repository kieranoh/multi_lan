package main

import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "encoding/hex"
    "fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
    var result [][2]string

    for i := 0; i < count; i++ {
        password := passwords[i]
        
        // Generate a random salt of the same length as the hash output
        salt := make([]byte, sha256.Size)
        _, err := rand.Read(salt)
        if err != nil {
            continue // You may want to handle the error appropriately
        }

        // Hash the password using PBKDF2-HMAC with SHA-256
        hashedPassword := pbkdf2.Key([]byte(password), salt, 10000, sha256.Size, sha256.New)

        // Convert both hash and salt to hex
        hashedPasswordHex := hex.EncodeToString(hashedPassword)
        saltHex := hex.EncodeToString(salt)

        // Append the results
        result = append(result, [2]string{hashedPasswordHex, saltHex})
    }

    return result
}

func main() {
    // This main function is only for the purpose of demonstrating how to call hashPasswords.
    // It is not part of the requested implementation. 
}