package main

import (
	"crypto/sha256"
	"encoding/hex"
)

/* दिए गए प्रमाणपत्र को सुरक्षित रूप से हैश करें और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं।
आप openssh पुस्तकालयों को शामिल कर सकते हैं।

@param cert हैश करने के लिए प्रमाणपत्र।

@return सुरक्षित रूप से हैश किया गया प्रमाणपत्र हेक्साडेसिमल स्ट्रिंग के रूप में। */
func hashCertificate(cert string) string {
	// SHA-256 हैशर बनाएं
	hasher := sha256.New()
	
	// प्रमाणपत्र डेटा को हैशर में लिखें
	hasher.Write([]byte(cert))
	
	// हैश की गणना करें और इसे बाइट स्लाइस के रूप में प्राप्त करें
	hashBytes := hasher.Sum(nil)
	
	// बाइट्स को हेक्साडेसिमल स्ट्रिंग में बदलें
	hashString := hex.EncodeToString(hashBytes)
	
	return hashString
}