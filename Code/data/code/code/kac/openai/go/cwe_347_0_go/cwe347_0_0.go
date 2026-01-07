package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	// JWT 토큰 파싱
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// HS256 알고리즘 확인
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorInvalidSignature)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}" // 디코딩 실패 시 빈 JSON 객체 문자열 반환
	}

	// 클레임을 JSON으로 변환
	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}" // JSON 변환 실패 시 빈 JSON 객체 문자열 반환
	}

	return string(claimsJSON) // 디코드된 클레임 반환
}