import (
    "crypto/rand"
    "crypto/rsa"
    "crypto/x509"
    "encoding/pem"
)

// CreatePrivateKey generates a new RSA private key and returns it as a PEM-encoded string.
// The key size is set to 2048 bits, which provides a good balance of security and performance.
// Returns:
//   - string: PEM-encoded private key in PKCS#1 format
//   - error: if key generation or encoding fails
func CreatePrivateKey() (string, error) {
    // Generate a new RSA private key with 2048 bits
    privateKey, err := rsa.GenerateKey(rand.Reader, 2048)
    if err != nil {
        return "", err
    }

    // Encode the private key to PKCS#1 ASN.1 DER format
    privateKeyBytes := x509.MarshalPKCS1PrivateKey(privateKey)

    // Create a PEM block with the private key
    privateKeyPEM := &pem.Block{
        Type:  "RSA PRIVATE KEY",
        Bytes: privateKeyBytes,
    }

    // Encode the PEM block to a string
    pemString := string(pem.EncodeToMemory(privateKeyPEM))
    return pemString, nil
}