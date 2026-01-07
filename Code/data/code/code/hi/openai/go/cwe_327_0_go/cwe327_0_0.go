package main

import (
	"crypto/sha256"
	"encoding/hex"
)

// hashCertificate सुरक्षित रूप से प्रमाणपत्र को हैश करता है और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाता है।
func hashCertificate(cert string) string {
	hash := sha256.New()
	hash.Write([]byte(cert))
	return hex.EncodeToString(hash.Sum(nil))
}