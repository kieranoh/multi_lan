import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The key size is set to 2048 bits. If key generation fails, an empty string is returned.
func CreatePrivateKey() string {
    // Generate a new RSA private key with 2048 bits
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return ""
    }

    // Convert the private key to PKCS#1 ASN.1 DER format
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

    // Create a PEM block with the private key data
    privateKeyPEM := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    }

    // Encode the PEM block to a string
    pemString := string(pem.EncodeToMemory(privateKeyPEM))
    return pemString
}