import (
	"encoding/json"
	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenStr string, key string) string {
	// Parse the token with the provided key
	token, err := jwt.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
		// Validate the signing method
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	// If parsing fails, return empty JSON object
	if err != nil || !token.Valid {
		return "{}"
	}

	// Extract claims
	if claims, ok := token.Claims.(jwt.MapClaims); ok {
		// Convert claims to JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	// Return empty JSON object if claims extraction fails
	return "{}"
}