package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken은 JWT를 디코드하고 클레임을 반환합니다.
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
func decodeJsonWebToken(token string, key string) string {
	claims := jwt.MapClaims{}
	tkn, err := jwt.ParseWithClaims(token, &claims, func(token *jwt.Token) (any, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("invalid signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !tkn.Valid {
		return "{}"
	}

	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON)
}