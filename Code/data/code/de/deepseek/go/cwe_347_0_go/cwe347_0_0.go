import (
	"encoding/json"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

func decodeJsonWebToken(tokenStr string, key string) string {
	// Versuche, das Token zu parsen und zu validieren
	token, err := jwt.Parse(tokenStr, func(token *jwt.Token) (interface{}, error) {
		// Überprüfe, ob der Signaturalgorithmus HS256 ist
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, jwt.ErrSignatureInvalid
		}
		return []byte(key), nil
	})

	// Wenn das Parsen fehlschlägt, gib leeres JSON-Objekt zurück
	if err != nil || !token.Valid {
		return "{}"
	}

	// Extrahiere die Claims
	if claims, ok := token.Claims.(jwt.MapClaims); ok {
		// Konvertiere die Claims zu JSON
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			return "{}"
		}
		return string(jsonBytes)
	}

	return "{}"
}