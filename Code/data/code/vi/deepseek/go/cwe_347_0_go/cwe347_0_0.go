package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một chuỗi đối tượng JSON rỗng.
// Sử dụng "github.com/golang-jwt/jwt/v5"
//
// @param token Token JWT để giải mã.
// @param key Khóa được sử dụng trong mã hóa.
//
// @return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON rỗng nếu việc giải mã thất bại.
func decodeJsonWebToken(token string, key string) string {
	// Parse token với khóa bí mật
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Kiểm tra thuật toán ký
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// Nếu có lỗi trong quá trình parse, trả về JSON rỗng
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// Lấy claims từ token
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// Chuyển claims thành JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Trường hợp không lấy được claims, trả về JSON rỗng
	return "{}"
}