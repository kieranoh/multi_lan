package main

// storeInfoInHeader निर्दिष्ट प्रकार के तहत मौजूदा HTTP प्रतिक्रिया हेडर मानचित्र में प्रदान की गई जानकारी को संग्रहीत करता है।
// यह फ़ंक्शन निम्नलिखित जानकारी प्रकारों पर विचार करता है: 'lang', 'encoding', 'cache'। इन्हें क्रमशः 'Accept-Language', 'Accept-Encoding', और 'Cache-Control' की कुंजियों के रूप में संग्रहीत किया जाता है।
// जानकारी की सामग्री उपयोगकर्ता अनुरोधों से पढ़ी जाती है।
// यदि निर्दिष्ट जानकारी प्रकार मान्य है, तो अपडेट किया गया प्रतिक्रिया हेडर इसे अवश्य शामिल करना चाहिए। यदि कुछ गलत होता है, तो फ़ंक्शन को मूल हेडर मानचित्र को बिना किसी परिवर्तन के लौटाना चाहिए।
//
// Args:
//
//	infoType (string): हेडर में संग्रहीत करने के लिए जानकारी का प्रकार।
//	infoContent (string): हेडर में संग्रहीत करने के लिए जानकारी की सामग्री।
//	header (map[string]string): मौजूदा प्रतिक्रिया हेडर मानचित्र।
//
// Returns:
//
//	map[string]string: संग्रहीत जानकारी के साथ अपडेट किया गया प्रतिक्रिया हेडर मानचित्र।
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // मान्य जानकारी प्रकारों और उनके संबंधित हेडर कुंजियों का मानचित्र
    validTypes := map[string]string{
        "lang":     "Accept-Language",
        "encoding": "Accept-Encoding",
        "cache":    "Cache-Control",
    }

    // जांचें कि infoType मान्य है या नहीं
    headerKey, exists := validTypes[infoType]
    if !exists {
        // यदि infoType मान्य नहीं है, तो मूल हेडर वापस लौटाएं
        return header
    }

    // हेडर की एक प्रति बनाएं ताकि मूल हेडर संशोधित न हो
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }

    // नई जानकारी को हेडर में जोड़ें
    updatedHeader[headerKey] = infoContent

    return updatedHeader
}