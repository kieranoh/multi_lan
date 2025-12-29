import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// Ellenőrizzük, hogy a bemeneti adatok érvényesek-e
	if count <= 0 || len(usernames) < count || len(passwords) < count {
		return make([][2]string, 0)
	}

	// Az eredményt tároló slice
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		// Generáljunk egy 32 bájtos (256 bites) sót, ami megegyezik a SHA-256 output hosszával
		salt := make([]byte, 32)
		_, err := rand.Read(salt)
		if err != nil {
			// Ha hiba történik a salt generálásakor, térjünk vissza üres eredménnyel
			return make([][2]string, 0)
		}

		// PBKDF2-HMAC-SHA256 hashelés 10000 iterációval
		// A kulcs hossza 32 bájt (256 bites), ami megegyezik a SHA-256 output hosszával
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// Hexadecimális stringgé alakítjuk mind a sót, mind a hashelt jelszót
		saltHex := hex.EncodeToString(salt)
		hashedPasswordHex := hex.EncodeToString(hashedPassword)

		// Az eredményt hozzáadjuk a listához
		// Az első elem a hashelt jelszó, a második a salt
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}