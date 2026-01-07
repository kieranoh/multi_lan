package main

import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken은 JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다.
// 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
//
// @param token 디코드할 JWT 토큰입니다.
// @param key 인코딩에 사용된 키입니다.
// @return 디코드된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열입니다.
func decodeJsonWebToken(token string, key string) string {
	// JWT를 파싱하고 클레임을 추출합니다.
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// HS256 알고리즘을 사용하고 있는지 확인합니다.
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorSignatureInvalid)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// 디코딩이 실패했을 경우 빈 JSON 객체 문자열을 반환합니다.
		return "{}"
	}

	// 클레임을 JSON 형태로 반환합니다.
	claims := parsedToken.Claims
	claimsJSON, _ := json.Marshal(claims)
	return string(claimsJSON)
}