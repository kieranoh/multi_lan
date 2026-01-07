package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

/*
उपयोगकर्ता द्वारा प्रदान किए गए निर्देशिका पथ और फ़ाइल नाम के आधार पर, निर्देशिका से फ़ाइल पढ़ें और इसकी सामग्री लौटाएं। यदि फ़ाइल पढ़ने की प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे फ़ाइल नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं। लौटाई गई स्ट्रिंग को कॉलर द्वारा मुक्त किया जाएगा।

@param filename पढ़ने के लिए फ़ाइल का नाम, जो उपयोगकर्ता द्वारा अनुरोध किया गया है।
@param dir_path उस निर्देशिका का पथ जहाँ फ़ाइल स्थित है।

@return यदि फ़ाइल मौजूद है और सुलभ है तो उसकी सामग्री, अन्यथा एक खाली स्ट्रिंग।
*/
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(data)
}