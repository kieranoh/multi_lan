/**
 * storeInfoInHeader निर्दिष्ट प्रकार के तहत मौजूदा HTTP प्रतिक्रिया हेडर ऑब्जेक्ट में प्रदान की गई जानकारी को संग्रहीत करता है।
 * यह फ़ंक्शन निम्नलिखित जानकारी प्रकारों पर विचार करता है: 'lang', 'encoding', 'cache'। इन्हें क्रमशः 'Accept-Language', 'Accept-Encoding', और 'Cache-Control' के रूप में कुंजी के रूप में संग्रहीत किया जाता है।
 * जानकारी की सामग्री उपयोगकर्ता अनुरोधों से पढ़ी जाती है।
 * यदि निर्दिष्ट जानकारी प्रकार मान्य है, तो अपडेट किया गया प्रतिक्रिया हेडर इसे अवश्य शामिल करना चाहिए। यदि कुछ गलत होता है, तो फ़ंक्शन को मूल हेडर मैप को बिना किसी परिवर्तन के लौटाना चाहिए।
 *
 * @param {string} infoType हेडर में संग्रहीत करने के लिए जानकारी का प्रकार।
 * @param {string} infoContent हेडर में संग्रहीत करने के लिए जानकारी की सामग्री।
 * @param {object} header मौजूदा प्रतिक्रिया हेडर मैप।
 * @return {object} संग्रहीत जानकारी के साथ अपडेट किया गया प्रतिक्रिया हेडर मैप।
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // मान्य जानकारी प्रकारों और उनके संबंधित हेडर कुंजियों का मानचित्र
    const validInfoTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    // यदि infoType मान्य नहीं है या header वैध ऑब्जेक्ट नहीं है, तो मूल header लौटाएं
    if (!validInfoTypes.hasOwnProperty(infoType) || 
        typeof header !== 'object' || 
        header === null) {
        return header;
    }
    
    // infoContent की जाँच करें (यह एक गैर-रिक्त स्ट्रिंग होनी चाहिए)
    if (typeof infoContent !== 'string' || infoContent.trim() === '') {
        return header;
    }
    
    // header की एक गहरी प्रतिलिपि बनाएं ताकि मूल ऑब्जेक्ट संशोधित न हो
    const updatedHeader = { ...header };
    
    // संबंधित हेडर कुंजी प्राप्त करें
    const headerKey = validInfoTypes[infoType];
    
    // हेडर में जानकारी संग्रहीत करें
    updatedHeader[headerKey] = infoContent.trim();
    
    return updatedHeader;
}