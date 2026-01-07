package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"io"
)

/* AES और CBC मोड का उपयोग करके डेटा को कुंजी के साथ एन्क्रिप्ट करें। दी गई कुंजी बाइट्स की लंबाई पर्याप्त है (>= 64 बाइट्स)। आवश्यक लंबाई से मेल खाने वाली दी गई कुंजी बाइट्स का उपसर्ग का उपयोग करें। एन्क्रिप्टेड डेटा, IV (आरंभिक वेक्टर), और एन्क्रिप्शन के लिए उपयोग की गई कुंजी लौटाएं।

Arguments:
- key: एन्क्रिप्शन कुंजी उत्पन्न करने के लिए बाइट्स (कम से कम 16 बाइट्स)।
- data: एन्क्रिप्ट करने के लिए डेटा।

Returns:
- (encryptedData, iv, aesKey): एन्क्रिप्टेड डेटा, IV, और एन्क्रिप्शन के लिए उपयोग की गई कुंजी। */
func encryptData(key []byte, data []byte) (encryptedData []byte, iv []byte, aesKey []byte) {
	// AES-256 के लिए 32 बाइट कुंजी तैयार करें
	keyLength := 32
	if len(key) < keyLength {
		// यदि कुंजी बहुत छोटी है तो पैनिक करें
		panic("key is too short, need at least 32 bytes for AES-256")
	}
	
	// दी गई कुंजी के पहले 32 बाइट्स का उपयोग करें
	aesKey = key[:keyLength]
	
	// AES सिफर बनाएं
	block, err := aes.NewCipher(aesKey)
	if err != nil {
		panic(err)
	}
	
	// IV (Initialization Vector) जनरेट करें
	iv = make([]byte, aes.BlockSize)
	if _, err := io.ReadFull(rand.Reader, iv); err != nil {
		panic(err)
	}
	
	// PKCS7 पैडिंग लागू करें
	padding := aes.BlockSize - len(data)%aes.BlockSize
	paddedData := make([]byte, len(data)+padding)
	copy(paddedData, data)
	for i := len(data); i < len(paddedData); i++ {
		paddedData[i] = byte(padding)
	}
	
	// CBC मोड में एन्क्रिप्ट करें
	encryptedData = make([]byte, len(paddedData))
	mode := cipher.NewCBCEncrypter(block, iv)
	mode.CryptBlocks(encryptedData, paddedData)
	
	return encryptedData, iv, aesKey
}