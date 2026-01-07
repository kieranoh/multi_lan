import (
	"encoding/json"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenStr string, key string) string {
	// 빈 토큰 문자열인 경우 빈 JSON 객체 반환
	if strings.TrimSpace(tokenStr) == "" {
		return "{}"
	}

	// JWT 파싱 및 검증
	token, err := jwt.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
		// HS256 알고리즘 확인
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	// 파싱 실패 시 빈 JSON 객체 반환
	if err != nil {
		return "{}"
	}

	// 토큰이 유효한지 확인
	if !token.Valid {
		return "{}"
	}

	// 클레임 추출
	claims, ok := token.Claims.(jwt.MapClaims)
	if !ok {
		return "{}"
	}

	// 클레임을 JSON 문자열로 변환
	jsonBytes, err := json.Marshal(claims)
	if err != nil {
		return "{}"
	}

	return string(jsonBytes)
}