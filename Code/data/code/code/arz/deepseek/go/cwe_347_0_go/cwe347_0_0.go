package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
	// 빈 JSON 객체 문자열을 기본값으로 설정
	emptyJSON := "{}"

	// 토큰이 비어있는지 확인
	if strings.TrimSpace(token) == "" {
		return emptyJSON
	}

	// JWT 파싱 및 검증
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// HS256 알고리즘 확인
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// 파싱 오류 처리
	if err != nil {
		return emptyJSON
	}

	// 토큰이 유효한지 확인
	if !parsedToken.Valid {
		return emptyJSON
	}

	// 클레임 추출
	claims, ok := parsedToken.Claims.(jwt.MapClaims)
	if !ok {
		return emptyJSON
	}

	// 클레임을 JSON 문자열로 변환
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return emptyJSON
	}

	return string(jsonBytes)
}