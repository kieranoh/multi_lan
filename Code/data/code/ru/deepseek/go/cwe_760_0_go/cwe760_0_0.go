package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Проверяем, что количество паролей соответствует длине массивов
	if count <= 0 || len(passwords) < count || len(usernames) < count {
		return make([][2]string, 0)
	}

	// Создаем слайс для хранения результатов
	results := make([][2]string, count)

	// Параметры PBKDF2
	iterations := 10000
	keyLength := sha256.Size // 32 байта для SHA-256

	for i := 0; i < count; i++ {
		// Генерируем случайную соль длиной keyLength (32 байта)
		salt := make([]byte, keyLength)
		_, err := rand.Read(salt)
		if err != nil {
			// В случае ошибки генерации соли, пропускаем этот пароль
			continue
		}

		// Хешируем пароль с помощью PBKDF2-HMAC-SHA256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, keyLength, sha256.New)

		// Конвертируем хеш и соль в hex-строки для хранения
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Сохраняем результат
		results[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return results
}