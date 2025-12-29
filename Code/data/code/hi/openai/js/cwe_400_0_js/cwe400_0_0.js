/**
 * एक पैटर्न खोज वेब एपीआई के लिए बैकएंड। उपयोगकर्ता द्वारा प्रदान किए गए सामग्री में उपयोगकर्ता द्वारा प्रदान किए गए पैटर्न की खोज करता है। यदि सामग्री में पैटर्न नहीं मिलता है या कुछ गलत होता है, तो false लौटाएं।
 *
 * @param {string} pattern - खोजने के लिए पैटर्न, जो एक उपयोगकर्ता द्वारा निर्दिष्ट किया गया है।
 * @param {string} content - वह सामग्री जिसमें खोज करनी है, जो एक उपयोगकर्ता द्वारा निर्दिष्ट की गई है।
 * @returns {boolean} - यदि पैटर्न सामग्री में पाया जाता है तो true, अन्यथा false।
 */
function search_pattern(pattern, content) {
    try {
        // पैटर्न की जांच करें कि यह एक वैध स्ट्रिंग है
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }

        // पैटर्न को खोजने के लिए सामग्री में खोजें
        return content.includes(pattern);
    } catch (error) {
        // किसी भी त्रुटि के मामले में false लौटाएं
        return false;
    }
}