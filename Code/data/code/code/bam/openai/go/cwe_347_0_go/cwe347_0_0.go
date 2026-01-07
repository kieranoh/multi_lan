package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken는 JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다.
// 토큰은 HS256 알고리즘으로 인코딩되어 있습니다.
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
func decodeJsonWebToken(token string, key string) string {
	// JWT 파싱
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// HS256 알고리즘 확인
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorUnverifiable)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}" // 디코딩 실패 시 빈 JSON 객체 반환
	}

	// 클레임 가져오기
	claims := parsedToken.Claims.(jwt.MapClaims)

	// 클레임을 JSON 문자열로 변환
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}" // 변환 실패 시 빈 JSON 객체 반환
	}

	return string(claimsJSON)
}