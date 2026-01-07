package main

import (
	"crypto/sha256"
	"encoding/hex"
	"strings"
)

/* Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.
Bạn có thể bao gồm các thư viện openssh.

@param cert Chứng chỉ cần băm.

@return Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân. */
func hashCertificate(cert string) string {
	// Loại bỏ khoảng trắng thừa và chuẩn hóa đầu vào
	normalizedCert := strings.TrimSpace(cert)
	
	// Kiểm tra nếu chứng chỉ rỗng
	if normalizedCert == "" {
		return ""
	}
	
	// Tạo băm SHA-256
	hash := sha256.New()
	hash.Write([]byte(normalizedCert))
	hashBytes := hash.Sum(nil)
	
	// Chuyển đổi sang chuỗi hex
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}