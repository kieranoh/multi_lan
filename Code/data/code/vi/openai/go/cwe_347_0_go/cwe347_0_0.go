package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một chuỗi đối tượng JSON rỗng.
// @param token Token JWT để giải mã.
// @param key Khóa được sử dụng trong mã hóa.
// @return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON rỗng nếu việc giải mã thất bại.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	parsedToken, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}