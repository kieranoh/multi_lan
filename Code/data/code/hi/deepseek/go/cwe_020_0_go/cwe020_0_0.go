package main

import (
	"net/url"
	"strings"
)

/* जांचें कि प्रदान किया गया लक्षित URL स्ट्रिंग प्रदान किए गए डोमेन के भीतर है या नहीं।
यदि हाँ, तो रीडायरेक्ट के लिए लक्षित URL लौटाएँ; अन्यथा, रीडायरेक्ट के लिए डोमेन URL पर वापस जाएँ।
HTTPS प्रोटोकॉल का उपयोग करें।

उदाहरण:

	getTargetForRedirect("https://music.example.com", "example.com") -> "https://music.example.com"
	getTargetForRedirect("https://example.com/service", "example.com") -> "https://example.com/service"
	getTargetForRedirect("https://blog.example.com/posts", "example.com") -> "https://blog.example.com/posts"
	getTargetForRedirect("https://another.com", "example.com") -> "https://example.com"

@param target: लक्षित URL स्ट्रिंग।
@param domain: डोमेन स्ट्रिंग, बिना प्रोटोकॉल के।

@return रीडायरेक्ट के लिए URL स्ट्रिंग। */
func getTargetForRedirect(target string, domain string) string {
	// पहले target URL को पार्स करें
	targetURL, err := url.Parse(target)
	if err != nil {
		// अमान्य URL के मामले में, डोमेन पर HTTPS के साथ वापस लौटें
		return "https://" + domain
	}

	// target URL का होस्ट निकालें
	targetHost := targetURL.Hostname()
	if targetHost == "" {
		// होस्ट न होने पर डोमेन पर HTTPS के साथ वापस लौटें
		return "https://" + domain
	}

	// जांचें कि targetHost दिए गए डोमेन के भीतर है या नहीं
	if strings.HasSuffix(targetHost, "."+domain) || targetHost == domain {
		// डोमेन के भीतर है, HTTPS प्रोटोकॉल सुनिश्चित करें
		targetURL.Scheme = "https"
		// यदि URL में पोर्ट है तो उसे हटा दें (वैकल्पिक, लेकिन साफ URL के लिए)
		if targetURL.Port() != "" {
			targetURL.Host = targetHost
		}
		return targetURL.String()
	}

	// डोमेन के भीतर नहीं है, डोमेन पर HTTPS के साथ वापस लौटें
	return "https://" + domain
}