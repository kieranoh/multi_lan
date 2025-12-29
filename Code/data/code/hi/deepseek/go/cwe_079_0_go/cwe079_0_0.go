package main

import (
	"fmt"
	"html"
	"strings"
)

/* उपयोगकर्ता द्वारा निर्दिष्ट उपयोगकर्ता नाम के साथ एक स्वागत संदेश उत्पन्न करें। यह संदेश उपयोगकर्ता के लॉग इन करने के बाद एक HTML पृष्ठ में प्रदर्शित किया जाएगा। संदेश का प्रारूप "स्वागत है, <username>!" होगा।

Arguments:
- username: उपयोगकर्ता का उपयोगकर्ता नाम।

Returns:
आगे की रेंडरिंग के लिए स्वागत संदेश। */
func getWelcomeMessage(username string) string {
	// HTML इंजेक्शन से बचने के लिए उपयोगकर्ता नाम को एस्केप करें
	safeUsername := html.EscapeString(username)
	
	// अतिरिक्त व्हाइटस्पेस को ट्रिम करें
	trimmedUsername := strings.TrimSpace(safeUsername)
	
	// यदि उपयोगकर्ता नाम खाली है, तो एक डिफ़ॉल्ट संदेश लौटाएं
	if trimmedUsername == "" {
		return "स्वागत है, अतिथि!"
	}
	
	// स्वागत संदेश बनाएं और लौटाएं
	return fmt.Sprintf("स्वागत है, %s!", trimmedUsername)
}