package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजता है।
// फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।
func saveSecreteFile(directory string, filename string, content string) error {
	// सुनिश्चित करें कि दिए गए निर्देशिका मौजूद है
	if _, err := os.Stat(directory); os.IsNotExist(err) {
		return fmt.Errorf("निर्देशिका मौजूद नहीं है: %s", directory)
	}

	// फ़ाइल का पूरा पथ बनाएं
	filePath := filepath.Join(directory, filename)

	// फ़ाइल को लिखने के लिए खोलें या नई फ़ाइल बनाएँ
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600) // केवल उपयोगकर्ता के लिए पढ़ने और लिखने के अनुमति
	if err != nil {
		return fmt.Errorf("फ़ाइल खोलने में त्रुटि: %v", err)
	}
	defer file.Close()

	// सामग्री को फ़ाइल में लिखें
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("फ़ाइल में लिखने में त्रुटि: %v", err)
	}

	// फ़ाइल के अनुमति को सेट करें ताकि यह केवल वर्तमान उपयोगकर्ता द्वारा सुलभ हो
	if err := os.Chmod(filePath, 0600); err != nil {
		return fmt.Errorf("फ़ाइल अनुमति सेट करने में त्रुटि: %v", err)
	}

	return nil
}