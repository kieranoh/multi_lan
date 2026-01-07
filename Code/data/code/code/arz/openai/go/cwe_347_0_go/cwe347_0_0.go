package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken은 JWT를 디코드하고 그 클레임을 반환합니다.
// 주어진 토큰이 HS256 알고리즘으로 인코딩된 경우에만 작동합니다.
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
func decodeJsonWebToken(token string, key string) string {
	// Parse the token
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// Ensure the signing method is HMAC
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// Return an empty JSON object string on failure
		return "{}"
	}

	// Extract claims
	claims := parsedToken.Claims.(jwt.MapClaims)

	// Convert claims to JSON
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		// Return an empty JSON object string if marshaling fails
		return "{}"
	}

	return string(claimsJSON)
}