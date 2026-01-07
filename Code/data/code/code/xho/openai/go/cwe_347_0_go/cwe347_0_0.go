package main

import (
	"encoding/json"
	"log"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken은 JWT를 디코드하고 그 클레임을 반환합니다.
// 토큰은 HS256 알고리즘으로 인코딩되어 있습니다.
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
// @param token 디코드할 JWT 토큰입니다.
// @param key 인코딩에 사용된 키입니다.
// @return 디코딩된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열입니다.
func decodeJsonWebToken(token string, key string) string {
	// JWT 문자열을 파싱합니다.
	parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		// HS256 알고리즘을 확인합니다.
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.NewValidationError("unexpected signing method", jwt.ValidationErrorMalformed)
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		// 오류가 발생하거나 토큰이 유효하지 않은 경우 빈 JSON 객체를 반환합니다.
		return "{}"
	}

	// 클레임을 추출합니다.
	claims := parsedToken.Claims.(jwt.MapClaims)

	// 클레임을 JSON 문자열로 변환합니다.
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		log.Println("Error marshalling claims to JSON:", err)
		return "{}"
	}

	return string(claimsJSON)
}