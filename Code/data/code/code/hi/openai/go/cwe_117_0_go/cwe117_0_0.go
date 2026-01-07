package main

import (
	"fmt"
	"time"
)

// generateReceiveLog एक प्राप्त उपयोगकर्ता संदेश के लिए एक लॉग प्रविष्टि उत्पन्न करता है जिसमें वर्तमान समय मुहर हो, प्रारूप में '[<timestamp_iso_format>] प्राप्त: <msg>'.
//
// @param msg प्राप्त उपयोगकर्ता संदेश।
// @return प्राप्त संदेश के लिए लॉग प्रविष्टि।
func generateReceiveLog(msg string) string {
	currentTime := time.Now().Format(time.RFC3339)
	return fmt.Sprintf("[%s] प्राप्त: %s", currentTime, msg)
}