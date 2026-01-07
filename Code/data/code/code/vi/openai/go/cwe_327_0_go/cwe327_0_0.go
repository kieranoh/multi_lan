package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.
// @param cert Chứng chỉ cần băm.
// @return Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân.
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}