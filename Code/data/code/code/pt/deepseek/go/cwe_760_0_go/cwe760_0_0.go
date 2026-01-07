package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Validação básica dos parâmetros de entrada
	if count <= 0 || len(usernames) < count || len(passwords) < count {
		return make([][2]string, 0)
	}

	// Inicializar slice para armazenar os resultados
	results := make([][2]string, count)

	// Parâmetros do PBKDF2
	iterations := 10000
	keyLength := sha256.Size // 32 bytes para SHA-256

	for i := 0; i < count; i++ {
		// Gerar sal aleatório do mesmo comprimento que o hash de saída
		salt := make([]byte, keyLength)
		_, err := rand.Read(salt)
		if err != nil {
			// Em caso de erro na geração do sal, usar um valor de fallback
			// baseado no nome de usuário para garantir consistência
			fallbackSalt := sha256.Sum256([]byte(usernames[i]))
			salt = fallbackSalt[:]
		}

		// Aplicar PBKDF2-HMAC-SHA256
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, iterations, keyLength, sha256.New)

		// Converter para representação hexadecimal para armazenamento
		hashedHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// Armazenar no formato [senha_hash, sal]
		results[i] = [2]string{hashedHex, saltHex}
	}

	return results
}