/**
 * एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजें।
 * फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।
 *
 * @param {string} directory - गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
 * @param {string} filename - गुप्त फ़ाइल का फ़ाइल नाम।
 * @param {string} content - गुप्त फ़ाइल की सामग्री।
 */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');

    const filePath = path.join(directory, filename);
    
    // गुप्त फ़ाइल को सहेजें
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}