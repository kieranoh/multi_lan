package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* 与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
オープンSSHライブラリを含めることができます。

@param cert ハッシュ化する証明書。

@return 安全にハッシュ化された証明書を16進数の文字列として。 */
func hashCertificate(cert string) string {
	// 証明書文字列の前後の空白を削除
	trimmedCert := strings.TrimSpace(cert)
	
	// 空の証明書の場合は空文字列を返す
	if trimmedCert == "" {
		return ""
	}
	
	// SHA-256ハッシュを計算
	hash := sha256.Sum256([]byte(trimmedCert))
	
	// 16進数文字列に変換
	hashString := hex.EncodeToString(hash[:])
	
	return hashString
}