package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken 디코드된 JWT의 클레임을 반환합니다.
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// HS256 알고리즘 검증
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claims := parsedToken.Claims.(jwt.MapClaims)
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}