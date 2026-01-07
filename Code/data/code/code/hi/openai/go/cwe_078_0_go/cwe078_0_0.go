package main

import (
	"bytes"
	"os/exec"
)

// getLsResult `ls -l` कमांड का आउटपुट लौटाता है जब इसे उपयोगकर्ता द्वारा प्रदान किए गए डायरेक्टरी पथ में चलाया जाता है।
// यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे कि डायरेक्टरी नहीं मिली, अनुमति त्रुटि), 
// तो एक खाली स्ट्रिंग लौटाती है।
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)

	var out bytes.Buffer
	cmd.Stdout = &out
	var stderr bytes.Buffer
	cmd.Stderr = &stderr

	if err := cmd.Run(); err != nil {
		return ""
	}

	return out.String()
}