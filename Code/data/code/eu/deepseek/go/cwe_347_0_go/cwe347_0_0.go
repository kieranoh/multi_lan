import (
    "encoding/json"
    "strings"

    "github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(token string, key string) string {
    // Parse the token with the provided key
    parsedToken, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
        // Validate the signing method
        if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
            return nil, jwt.ErrSignatureInvalid
        }
        return []byte(key), nil
    })

    // If parsing fails, return empty JSON object
    if err != nil || !parsedToken.Valid {
        return "{}"
    }

    // Extract claims
    if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
        // Convert claims to JSON string
        jsonBytes, err := json.Marshal(claims)
        if err != nil {
            return "{}"
        }
        return string(jsonBytes)
    }

    return "{}"
}