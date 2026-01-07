import (
    "encoding/json"
    "strings"
    
    "github.com/golang-jwt/jwt/v5"
)

// JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.
// "github.com/golang-jwt/jwt/v5"를 사용하세요.
//
// @param token 디코드할 JWT 토큰입니다.
// @param key 인코딩에 사용된 키입니다.
//
// @return 디코딩된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열입니다.
func decodeJsonWebToken(token string, key string) string {
    // 빈 토큰 체크
    if strings.TrimSpace(token) == "" {
        return "{}"
    }
    
    // JWT 파싱 및 검증
    parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
        // 알고리즘 검증
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
    
    return "{}"
}