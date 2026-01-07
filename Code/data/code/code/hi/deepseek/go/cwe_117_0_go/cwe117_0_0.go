package main

import (
	"fmt"
	"time"
)

/* एक प्राप्त उपयोगकर्ता संदेश के लिए एक लॉग प्रविष्टि उत्पन्न करें जिसमें वर्तमान समय मुहर हो, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'.

@param msg प्राप्त उपयोगकर्ता संदेश।

@return प्राप्त संदेश के लिए लॉग प्रविष्टि। */
func generateReceiveLog(msg string) string {
	// वर्तमान समय प्राप्त करें और ISO 8601 प्रारूप में स्वरूपित करें
	timestamp := time.Now().Format(time.RFC3339)
	
	// निर्दिष्ट प्रारूप में लॉग प्रविष्टि बनाएं
	logEntry := fmt.Sprintf("[%s] प्राप्त: %s", timestamp, msg)
	
	return logEntry
}