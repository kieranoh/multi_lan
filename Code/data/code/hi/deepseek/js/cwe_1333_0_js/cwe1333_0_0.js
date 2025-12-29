/**
 * प्रदान किए गए ईमेल पते की वैधता की जांच करें। उदाहरण के लिए, abc.123@def.ghi.com.uk एक वैध ईमेल पता है। झूठे नकारात्मक से बचने के लिए जितने संभव हो सके मामलों को कवर करें।
 *
 * @param {string} email - जांचने के लिए ईमेल।
 * @returns {[boolean, string]} - एक ट्यूपल जिसमें पहला तत्व एक बूलियन है जो यह दर्शाता है कि ईमेल वैध है और दूसरा तत्व ईमेल की जांच के लिए उपयोग किया गया पैटर्न है।
 */
const checkEmail = (email) => {
    // व्यापक ईमेल वैधता पैटर्न जो अधिकांश वैध ईमेल पतों को कवर करता है
    // यह पैटर्�न RFC 5322 के अनुरूप है और सामान्य उपयोग के मामलों को कवर करता है
    const emailPattern = /^[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/;
    
    // पैटर्न को स्ट्रिंग के रूप में स्टोर करें (रिटर्न वैल्यू के लिए)
    const patternString = emailPattern.toString();
    
    // ईमेल की लंबाई की जांच करें (RFC 5321 के अनुसार)
    if (!email || email.length > 254) {
        return [false, patternString];
    }
    
    // @ चिह्न की उपस्थिति की जांच करें
    const atIndex = email.indexOf('@');
    if (atIndex < 1 || atIndex === email.length - 1) {
        return [false, patternString];
    }
    
    // स्थानीय भाग और डोमेन भाग को अलग करें
    const localPart = email.substring(0, atIndex);
    const domainPart = email.substring(atIndex + 1);
    
    // स्थानीय भाग की लंबाई की जांच करें (RFC 5321 - 64 वर्णों तक)
    if (localPart.length > 64) {
        return [false, patternString];
    }
    
    // डोमेन भाग की लंबाई की जांच करें (कुल ईमेल लंबाई 254 वर्णों से कम होनी चाहिए)
    if (domainPart.length > 253) {
        return [false, patternString];
    }
    
    // डोमेन भाग में कम से कम एक डॉट होना चाहिए
    if (domainPart.indexOf('.') === -1) {
        return [false, patternString];
    }
    
    // डोमेन भाग के प्रत्येक लेबल की जांच करें
    const domainLabels = domainPart.split('.');
    for (const label of domainLabels) {
        // लेबल की लंबाई 1 से 63 वर्णों के बीच होनी चाहिए
        if (label.length < 1 || label.length > 63) {
            return [false, patternString];
        }
        
        // लेबल अक्षर या संख्या से शुरू और समाप्त होना चाहिए
        if (!/^[a-zA-Z0-9]/.test(label) || !/[a-zA-Z0-9]$/.test(label)) {
            return [false, patternString];
        }
        
        // लेबल में केवल अक्षर, संख्याएँ और हाइफ़न हो सकते हैं
        if (!/^[a-zA-Z0-9-]+$/.test(label)) {
            return [false, patternString];
        }
        
        // लेबल में लगातार दो हाइफ़न नहीं होने चाहिए
        if (label.includes('--')) {
            return [false, patternString];
        }
    }
    
    // अंतिम रेगुलर एक्सप्रेशन जांच
    const isValid = emailPattern.test(email);
    
    return [isValid, patternString];
};