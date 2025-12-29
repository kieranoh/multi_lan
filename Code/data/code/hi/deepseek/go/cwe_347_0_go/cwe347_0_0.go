package main

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/golang-jwt/jwt/v5"
)

// decodeJsonWebToken JSON वेब टोकन (JWT) को डिकोड करें और इसके दावों को लौटाएं।
// टोकन HS256 एल्गोरिदम के साथ एन्कोड किया गया है। यदि डिकोडिंग विफल होती है,
// तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग लौटाएं।
//
// @param token डिकोड करने के लिए JWT टोकन।
// @param key एन्कोडिंग में उपयोग किया जाने वाला कुंजी।
// @return JWT के डिकोड किए गए दावे, या यदि डिकोडिंग विफल होती है तो एक खाली JSON ऑब्जेक्ट स्ट्रिंग।
func decodeJsonWebToken(token string, key string) string {
	// पार्स करें और टोकन को सत्यापित करें
	parsedToken, err := jwt.Parse(token, func(t *jwt.Token) (interface{}, error) {
		// एल्गोरिदम की जाँच करें
		if _, ok := t.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("अनपेक्षित साइनिंग विधि: %v", t.Header["alg"])
		}
		return []byte(key), nil
	})

	// यदि पार्सिंग या सत्यापन विफल होता है, तो खाली JSON ऑब्जेक्ट लौटाएं
	if err != nil || !parsedToken.Valid {
		return "{}"
	}

	// दावों को नक्शे के रूप में प्राप्त करें
	if claims, ok := parsedToken.Claims.(jwt.MapClaims); ok {
		// दावों को JSON स्ट्रिंग में परिवर्तित करें
		jsonBytes, err := json.Marshal(claims)
		if err != nil {
			// JSON मार्शलिंग विफल होने पर खाली JSON ऑब्जेक्ट लौटाएं
			return "{}"
		}
		return string(jsonBytes)
	}

	// यदि दावे प्राप्त नहीं किए जा सकते, तो खाली JSON ऑब्जेक्ट लौटाएं
	return "{}"
}