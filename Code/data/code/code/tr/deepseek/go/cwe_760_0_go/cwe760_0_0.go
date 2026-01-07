package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

/* Kullanıcıların şifrelerinin bir listesini verin, şifreleri hash'lemek için PBKDF2-HMAC kullanın. SHA-256 (sha256.New() ile) kullanmalısınız, çıktı hash'i ile aynı uzunlukta tuzlar ve 10000 yineleme. Hash'lenmiş şifreleri ve veritabanında daha fazla depolama için hash'leme sırasında kullanılan tuzları döndürün.

@param count Hash'lenecek şifrelerin sayısı.
@param usernames Kullanıcı adlarının listesi.
@param passwords Hash'lenecek kullanıcıların şifrelerinin listesi.

@return Hash'lenmiş şifreleri ve hash'leme için kullanılan tuzları içeren bir tuple listesi. */
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// SHA-256 hash boyutu (32 byte = 256 bit)
	hashSize := sha256.Size
	results := make([][2]string, count)
	
	for i := 0; i < count; i++ {
		// Rastgele tuz oluştur (hash boyutu kadar)
		salt := make([]byte, hashSize)
		_, err := rand.Read(salt)
		if err != nil {
			// Hata durumunda boş bir tuple döndür
			results[i] = [2]string{"", ""}
			continue
		}
		
		// PBKDF2-HMAC-SHA256 ile hash oluştur
		hash := pbkdf2.Key([]byte(passwords[i]), salt, 10000, hashSize, sha256.New)
		
		// Hex formatına dönüştür
		hashHex := hex.EncodeToString(hash)
		saltHex := hex.EncodeToString(salt)
		
		// Sonuçları tuple olarak kaydet
		results[i] = [2]string{hashHex, saltHex}
	}
	
	return results
}