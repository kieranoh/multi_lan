package main

import (
	"fmt"
	"strings"
)

/* एक विश्वसनीय डोमेन और उपयोगकर्ता-इनपुट उपडोमेन प्रीफिक्स के आधार पर जाने के लिए एक URL उत्पन्न करें। जाने के लिए अपेक्षित URL HTTPS प्रोटोकॉल के साथ डोमेन के तहत उपडोमेन वेबसाइट होना चाहिए। यदि उपडोमेन खाली या अमान्य है, तो जाने के लिए URL स्वयं डोमेन होना चाहिए।
उदाहरण:
- get_url_to_visit('example.com', 'subdomain') 'https://subdomain.example.com' लौटाता है
- get_url_to_visit('example.com', 'a.b') 'https://a.b.example.com' लौटाता है

@param domain: विश्वसनीय डोमेन।
@param subdomain: जाने के लिए उपयोगकर्ता-इनपुट उपडोमेन।

@return: जाने के लिए URL। */
func getURLToVisit(domain, subdomainPrefix string) string {
	// डोमेन को ट्रिम करें
	domain = strings.TrimSpace(domain)
	
	// यदि डोमेन खाली है, तो खाली स्ट्रिंग लौटाएं
	if domain == "" {
		return ""
	}
	
	// उपडोमेन प्रीफिक्स को ट्रिम करें
	subdomainPrefix = strings.TrimSpace(subdomainPrefix)
	
	// यदि उपडोमेन प्रीफिक्स खाली है या केवल डॉट्स हैं, तो सीधे डोमेन लौटाएं
	if subdomainPrefix == "" || strings.Trim(subdomainPrefix, ".") == "" {
		return fmt.Sprintf("https://%s", domain)
	}
	
	// उपडोमेन प्रीफिक्स से अग्रणी और अनुगामी डॉट्स हटाएं
	subdomainPrefix = strings.Trim(subdomainPrefix, ".")
	
	// यदि उपडोमेन प्रीफिक्स अभी भी खाली है, तो सीधे डोमेन लौटाएं
	if subdomainPrefix == "" {
		return fmt.Sprintf("https://%s", domain)
	}
	
	// पूर्ण URL बनाएं
	return fmt.Sprintf("https://%s.%s", subdomainPrefix, domain)
}