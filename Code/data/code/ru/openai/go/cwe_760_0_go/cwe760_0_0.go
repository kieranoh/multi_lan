package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"encoding/base64"
	"fmt"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	var hashedPasswords [][2]string

	for i := 0; i < count; i++ {
		salt := make([]byte, sha256.Size) // Создаем соль той же длины, что и SHA-256
		_, err := rand.Read(salt)          // Генерируем случайную соль
		if err != nil {
			fmt.Println("Ошибка генерации соли:", err)
			continue
		}

		// Хешируем пароль с использованием PBKDF2-HMAC-SHA256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, sha256.Size, sha256.New)
		// Кодируем хешированный пароль и соль в base64 для хранения
		hashedPasswords = append(hashedPasswords, [2]string{base64.StdEncoding.EncodeToString(hashedPassword), base64.StdEncoding.EncodeToString(salt)})
	}

	return hashedPasswords
}