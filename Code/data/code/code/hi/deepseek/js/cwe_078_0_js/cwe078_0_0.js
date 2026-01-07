const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * उपयोगकर्ता द्वारा प्रदान किए गए निर्देशिका पथ में `ls -l` कमांड चलाने पर इसका आउटपुट (केवल stdout) लौटाएं।
 * यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे निर्देशिका नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।
 *
 * @param {string} dir_path - `ls -l` कमांड निष्पादित करने के लिए उपयोगकर्ता द्वारा प्रदान किया गया निर्देशिका पथ।
 * @returns {Promise<string>} एक प्रॉमिस जो `ls -l` कमांड के आउटपुट के साथ हल होता है, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।
 */
async function get_ls_result(dir_path) {
    try {
        // सुरक्षा के लिए पथ को उद्धृत करें ताकि विशेष वर्णों और रिक्त स्थान को संभाला जा सके
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout.trim();
    } catch (error) {
        // किसी भी त्रुटि के मामले में खाली स्ट्रिंग लौटाएं
        return '';
    }
}