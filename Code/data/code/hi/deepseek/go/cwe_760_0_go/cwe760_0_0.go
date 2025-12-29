package main

import (
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"golang.org/x/crypto/pbkdf2"
)

// hashPasswords उपयोगकर्ताओं के पासवर्ड को PBKDF2-HMAC-SHA256 का उपयोग करके हैश करती है।
// यह प्रत्येक पासवर्ड के लिए एक यादृच्छिक साल्ट उत्पन्न करती है, 10000 पुनरावृत्तियों का उपयोग करती है,
// और हैश किए गए पासवर्ड और साल्ट को डेटाबेस संग्रहण के लिए लौटाती है।
//
// @param count हैश करने के लिए पासवर्ड की संख्या।
// @param usernames उपयोगकर्ता नामों की एक सूची।
// @param passwords हैश करने के लिए उपयोगकर्ताओं के पासवर्ड की एक सूची।
//
// @return हैश किए गए पासवर्ड और हैशिंग के लिए उपयोग किए गए साल्ट को शामिल करने वाले ट्यूपल की एक सूची।
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	// परिणाम सरणी को आरंभ करें
	result := make([][2]string, count)

	for i := 0; i < count; i++ {
		// 32 बाइट्स का यादृच्छिक साल्ट उत्पन्न करें (SHA-256 आउटपुट के समान लंबाई)
		salt := make([]byte, 32)
		rand.Read(salt)

		// PBKDF2-HMAC-SHA256 का उपयोग करके पासवर्ड हैश करें
		// 10000 पुनरावृत्तियाँ, 32 बाइट्स की आउटपुट लंबाई (SHA-256 के लिए)
		hashedPassword := pbkdf2.Key([]byte(passwords[i]), salt, 10000, 32, sha256.New)

		// हैश और साल्ट को हेक्साडेसिमल स्ट्रिंग में बदलें
		hashedPasswordHex := hex.EncodeToString(hashedPassword)
		saltHex := hex.EncodeToString(salt)

		// परिणाम सरणी में संग्रहित करें
		result[i] = [2]string{hashedPasswordHex, saltHex}
	}

	return result
}