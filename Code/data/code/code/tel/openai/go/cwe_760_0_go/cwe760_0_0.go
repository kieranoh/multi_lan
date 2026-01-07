package main

import (
    "crypto/rand"
    "crypto/sha256"
    "golang.org/x/crypto/pbkdf2"
    "encoding/hex"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
    result := make([][2]string, count)

    for i := 0; i < count; i++ {
        salt := make([]byte, 32) // Generate a 256-bit (32 bytes) salt
        _, err := rand.Read(salt)
        if err != nil {
            panic(err) // handle error appropriately in production code
        }

        hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)
        result[i][0] = hex.EncodeToString(hashedPassword)
        result[i][1] = hex.EncodeToString(salt)
    }

    return result
}