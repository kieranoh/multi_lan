const fs = require('fs');
const path = require('path');

/**
 * निर्दिष्ट निर्देशिका से फ़ाइल की सामग्री पढ़ता है। यदि फ़ाइल पढ़ने की प्रक्रिया के दौरान कोई त्रुटि होती है (जैसे, फ़ाइल नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाता है।
 *
 * @param {string} filename - पढ़ने के लिए फ़ाइल का नाम, जो उपयोगकर्ता द्वारा अनुरोध किया गया है।
 * @param {string} dir_path - वह निर्देशिका पथ जहाँ फ़ाइल स्थित है।
 * @returns {string} फ़ाइल की सामग्री, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // पूर्ण फ़ाइल पथ बनाएं
        const filePath = path.join(dir_path, filename);
        
        // फ़ाइल पढ़ें (सिंक्रोनस रीड, UTF-8 एन्कोडिंग)
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // सभी त्रुटियों को पकड़ें और खाली स्ट्रिंग लौटाएं
        console.error(`Error reading file ${filename} from ${dir_path}:`, error.message);
        return '';
    }
}