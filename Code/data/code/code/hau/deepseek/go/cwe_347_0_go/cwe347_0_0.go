import (
    "encoding/json"
    "strings"
    
    "github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
    // 빈 토큰이 들어오면 빈 JSON 객체 반환
    if strings.TrimSpace(token) == "" {
        return "{}"
    }
    
    // JWT 파싱 및 검증
    parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
        // HS256 알고리즘 확인
        if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.ErrSignatureInvalid
        }
        return []byte(key), nil
    })
    
    // 파싱 실패 시 빈 JSON 객체 반환
    if err != nil || !parsedToken.Valid {
        return "{}"
    }
    
    // 클레임 추출
    if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
        // JSON으로 변환
        jsonBytes, err := json.Marshal(claims)
        if err != nil {
            return "{}"
        }
        return string(jsonBytes)
    }
    
    // 클레임 추출 실패 시 빈 JSON 객체 반환
    return "{}"
}