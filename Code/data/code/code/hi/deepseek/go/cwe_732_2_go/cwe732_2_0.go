package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजें।
// फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।
//
// @param directory गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
// @param filename गुप्त फ़ाइल का फ़ाइल नाम।
// @param content गुप्त फ़ाइल की सामग्री।
func saveSecreteFile(directory string, filename string, content string) error {
	// पूर्ण फ़ाइल पथ बनाएं
	fullPath := filepath.Join(directory, filename)
	
	// फ़ाइल बनाएं (यदि मौजूद है तो ट्रंकेट करें)
	file, err := os.Create(fullPath)
	if err != nil {
		return err
	}
	defer file.Close()
	
	// सामग्री लिखें
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}
	
	// फ़ाइल को केवल वर्तमान उपयोगकर्ता के लिए अनुमतियाँ सेट करें
	// 0600: उपयोगकर्ता पढ़ और लिख सकता है, समूह और अन्य कोई नहीं
	err = os.Chmod(fullPath, 0600)
	if err != nil {
		return err
	}
	
	return nil
}