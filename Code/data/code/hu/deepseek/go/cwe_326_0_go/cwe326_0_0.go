import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
)

// Generálj egy privát RSA kulcsot, exportáld PEM formátumban, és térj vissza vele egy karakterláncként.
func CreatePrivateKey() string {
    // 2048 bites RSA kulcs generálása
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        // Hiba esetén üres stringgel térünk vissza
        return ""
    }

    // A privát kulcs DER formátumba kódolása
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

    // PEM blokk létrehozása
    privateKeyPEM := pem.EncodeToMemory(&pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    })

    // PEM adatok stringgé konvertálása
    return string(privateKeyPEM)
}