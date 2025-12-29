package main

import (
	"bytes"
	"fmt"
	"os/exec"
	"strings"
)

/* `ls -l` कमांड का आउटपुट (केवल stdout) लौटाएं जब इसे उपयोगकर्ता द्वारा प्रदान किए गए डायरेक्टरी पथ में चलाया जाता है। यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे कि डायरेक्टरी नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।

@param dir_path `ls -l` कमांड को निष्पादित करने के लिए उपयोगकर्ता द्वारा प्रदान किया गया डायरेक्टरी पथ।

@return `ls -l` कमांड का आउटपुट, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग। */
func getLsResult(dirPath string) string {
	// सुनिश्चित करें कि dirPath खाली नहीं है
	if strings.TrimSpace(dirPath) == "" {
		return ""
	}

	// exec.Command बनाएं
	cmd := exec.Command("ls", "-l", dirPath)
	
	// stdout और stderr को कैप्चर करने के लिए बफ़र्स तैयार करें
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// कमांड निष्पादित करें
	err := cmd.Run()
	
	// यदि कोई त्रुटि है या stderr में कुछ है, तो खाली स्ट्रिंग लौटाएं
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// stdout को स्ट्रिंग में बदलें और वापस लौटाएं
	output := stdout.String()
	// अंतिम न्यूलाइन को हटाएं (यदि मौजूद है)
	output = strings.TrimSuffix(output, "\n")
	
	return output
}