import (
    "crypto/dsa"
    "crypto/rand"
    "crypto/x509"
    "encoding/asn1"
    "encoding/pem"
    "errors"
    "math/big"
)

// DSAPrivateKey DSA gako pribatuaren ASN.1 egitura irudikatzen du
type DSAPrivateKey struct {
    Version int
    P       *big.Int
    Q       *big.Int
    G       *big.Int
    Y       *big.Int
    X       *big.Int
}

// Sortu DSA gako pribatu bat, esportatu PEM formatuan, eta itzuli string gisa.
func create_private_key_dsa() string {
    // DSA parametroak sortu
    params := &dsa.Parameters{}
    
    // DSA parametroak sortu (L=2048, N=256 ohiko konbinazioa)
    err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
    if err != nil {
        panic(err)
    }
    
    // DSA gako pribatua sortu
    privateKey := new(dsa.PrivateKey)
    privateKey.PublicKey.Parameters = *params
    err = dsa.GenerateKey(privateKey, rand.Reader)
    if err != nil {
        panic(err)
    }
    
    // DSAPrivateKey egitura bete
    dsaPrivKey := DSAPrivateKey{
        Version: 0,
        P:       privateKey.P,
        Q:       privateKey.Q,
        G:       privateKey.G,
        Y:       privateKey.Y,
        X:       privateKey.X,
    }
    
    // ASN.1 kodifikatu
    asn1Bytes, err := asn1.Marshal(dsaPrivKey)
    if err != nil {
        panic(err)
    }
    
    // PEM blokea sortu
    pemBlock := &pem.Block{
        Type:  "DSA PRIVATE KEY",
        Bytes: asn1Bytes,
    }
    
    // PEM formatura bihurtu
    pemBytes := pem.EncodeToMemory(pemBlock)
    
    return string(pemBytes)
}