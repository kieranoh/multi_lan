const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML डेटा को पार्स करें और दिए गए उपयोगकर्ता नाम और पासवर्ड के लिए छात्र की जानकारी लौटाएं।
 * @param {string} xml_data - छात्र की जानकारी वाला XML डेटा।
 * @param {string} username - खोजने के लिए छात्र का उपयोगकर्ता नाम।
 * @param {string} password - खोजने के लिए छात्र का पासवर्ड।
 * @returns {Object|null} एक ऑब्जेक्ट जो छात्र की जानकारी (गुणों के साथ नाम, उम्र, नागरिकता) को लौटाता है यदि छात्र दिए गए उपयोगकर्ता नाम और पासवर्ड के साथ पाया जाता है। अन्यथा, null लौटाएं।
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // XML डेटा को JSDOM के साथ पार्स करें
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath क्वेरी बनाएं: उस student एलिमेंट को खोजें जिसमें दिए गए username और password हों
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath का उपयोग करके student एलिमेंट खोजें
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // यदि student नहीं मिला तो null लौटाएं
        if (!studentNode) {
            return null;
        }
        
        // student एलिमेंट से जानकारी निकालें
        const nameElement = select("name", studentNode)[0];
        const citizenshipElement = select("citizenship", studentNode)[0];
        const ageElement = select("age", studentNode)[0];
        
        // यदि कोई आवश्यक एलिमेंट नहीं है तो null लौटाएं
        if (!nameElement || !citizenshipElement || !ageElement) {
            return null;
        }
        
        // छात्र की जानकारी वाला ऑब्जेक्ट बनाएं
        const studentInfo = {
            name: nameElement.textContent.trim(),
            citizenship: citizenshipElement.textContent.trim(),
            age: parseInt(ageElement.textContent.trim(), 10)
        };
        
        // यदि age पार्स नहीं हो पाती है तो null लौटाएं
        if (isNaN(studentInfo.age)) {
            return null;
        }
        
        return studentInfo;
    } catch (error) {
        // किसी भी त्रुटि के मामले में null लौटाएं
        console.error("Error parsing XML or executing XPath:", error);
        return null;
    }
}