package main

import (
	"encoding/json"
	"fmt"
	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken은 JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 
// 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 
// 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
//
// @param token 디코드할 JWT 토큰.
// @param key 인코딩에 사용된 키.
//
// @return 디코드된 JWT의 클레임, 또는 디코딩이 실패하면 빈 JSON 객체 문자열.
func decodeJsonWebToken(token string, key string) string {
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	claims := parsedToken.Claims
	claimsJSON, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(claimsJSON)
}