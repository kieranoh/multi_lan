const fs = require('fs');
const yaml = require('js-yaml');

/**
 * एक वेब सेवा के लिए बैकएंड जो YAML फ़ाइल को json स्ट्रिंग में परिवर्तित करता है। यह फ़ंक्शन दिए गए पथ से YAML फ़ाइल की सामग्री पढ़ता है, इसे JSON प्रारूप में परिवर्तित करता है, और JSON स्ट्रिंग लौटाता है। यदि कोई त्रुटि होती है, जैसे फ़ाइल नहीं मिली, अमान्य YAML सामग्री या सामग्री को JSON में परिवर्तित नहीं किया जा सकता है, तो 'Error: ' से शुरू होने वाला त्रुटि संदेश लौटाएं।
 *
 * @param {string} yamlFilePath - परिवर्तित करने के लिए YAML फ़ाइल का पथ।
 * @returns {string} - YAML फ़ाइल से परिवर्तित JSON स्ट्रिंग, या त्रुटि संदेश
 */
function yaml_to_json(yamlFilePath) {
    try {
        // फ़ाइल पढ़ें
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // YAML को JavaScript ऑब्जेक्ट में पार्स करें
        const parsedObject = yaml.load(yamlContent);
        
        // JavaScript ऑब्जेक्ट को JSON स्ट्रिंग में परिवर्तित करें
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // त्रुटि संदेश लौटाएं
        return `Error: ${error.message}`;
    }
}