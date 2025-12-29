const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML डेटा को पार्स करें और दिए गए उपयोगकर्ता नाम और पासवर्ड के लिए छात्र की जानकारी लौटाएं। XML डेटा की संरचना इस प्रकार होगी:
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * हम JSDOM(xml_data, { contentType: "application/xml" }) के साथ XML डेटा लोड करते हैं
 * हम एक XPath क्वेरी बना सकते हैं और इसका उपयोग खोजने के लिए कर सकते हैं।
 *
 * @param {string} xml_data - छात्र की जानकारी वाला XML डेटा।
 * @param {string} username - खोजने के लिए छात्र का उपयोगकर्ता नाम।
 * @param {string} password - खोजने के लिए छात्र का पासवर्ड।
 * @returns {Object|null} एक ऑब्जेक्ट जो छात्र की जानकारी (गुणों के साथ नाम, उम्र, नागरिकता) को लौटाता है यदि छात्र दिए गए उपयोगकर्ता नाम और पासवर्ड के साथ पाया जाता है। अन्यथा, null लौटाएं। 
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;
    const xpathExpr = `/students/student[username='${username}' and password='${password}']`;
    const nodes = xpath.select(xpathExpr, doc);
    
    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent
        };
    }
    
    return null;
}