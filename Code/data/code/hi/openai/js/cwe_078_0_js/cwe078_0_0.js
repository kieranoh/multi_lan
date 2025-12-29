const { exec } = require('child_process');

/**
 * उपयोगकर्ता द्वारा प्रदान किए गए निर्देशिका पथ में `ls -l` कमांड चलाने पर इसका आउटपुट (केवल stdout) लौटाएं। यदि कमांड निष्पादन के दौरान कोई त्रुटि होती है (जैसे निर्देशिका नहीं मिली, अनुमति त्रुटि), तो एक खाली स्ट्रिंग लौटाएं।
 *
 * @param {string} dir_path - `ls -l` कमांड निष्पादित करने के लिए उपयोगकर्ता द्वारा प्रदान किया गया निर्देशिका पथ।
 * @returns {Promise<string>} एक प्रॉमिस जो `ls -l` कमांड के आउटपुट के साथ हल होता है, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}