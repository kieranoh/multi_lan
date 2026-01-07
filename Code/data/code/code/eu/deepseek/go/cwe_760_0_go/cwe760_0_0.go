import (
    "crypto/rand"
    "crypto/sha256"
    "encoding/hex"
    "golang.org/x/crypto/pbkdf2"
)

func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
    // Emaitza gordetzeko arraya hasieratu
    result := make([][2]string, count)
    
    for i := 0; i < count; i++ {
        // Salt ausazko 32 byteko sortu (SHA-256 hasharen luzera bera)
        salt := make([]byte, 32)
        rand.Read(salt)
        
        // PBKDF2-HMAC-SHA256 erabiliz pasahitza hashatu
        hashedPassword := pbkdf2.Key(
            []byte(passwords[i]),
            salt,
            10000,     // iterazio kopurua
            32,        // irteerako hash luzera (32 byte = 256 bit)
            sha256.New,
        )
        
        // Salt eta hashedPassword hexadezimal bihurtu
        saltHex := hex.EncodeToString(salt)
        hashedPasswordHex := hex.EncodeToString(hashedPassword)
        
        // Emaitza gorde: [salt, hashedPassword]
        result[i] = [2]string{saltHex, hashedPasswordHex}
    }
    
    return result
}