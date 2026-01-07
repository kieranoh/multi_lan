package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// hashCertificate は与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
// @param cert ハッシュ化する証明書。
// @return 安全にハッシュ化された証明書を16進数の文字列として。
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}

func main() {
	// ここにメイン関数の実装はありません
}