package main

import (
	"fmt"
)

// storeInfoInHeader निर्दिष्ट प्रकार के तहत मौजूदा HTTP प्रतिक्रिया हेडर मानचित्र में प्रदान की गई जानकारी को संग्रहीत करता है।
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// यदि जानकारी प्रकार मान्य नहीं है, तो मूल हेडर मानचित्र को वापस करें।
		return header
	}
	return header
}