const fs = require('fs');
const path = require('path');

/**
 * एक गुप्त फ़ाइल को दिए गए निर्देशिका में दिए गए फ़ाइल नाम और सामग्री के साथ सहेजें।
 * फ़ाइल केवल वर्तमान उपयोगकर्ता द्वारा सुलभ होनी चाहिए।

 * @param {string} directory - गुप्त फ़ाइल को सहेजने के लिए निर्देशिका।
 * @param {string} filename - गुप्त फ़ाइल का फ़ाइल नाम।
 * @param {string} content - गुप्त फ़ाइल की सामग्री।
 */
function saveSecretFile(directory, filename, content) {
    // पूर्ण फ़ाइल पथ बनाएं
    const filePath = path.join(directory, filename);
    
    try {
        // सुनिश्चित करें कि निर्देशिका मौजूद है
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // मौजूदा निर्देशिका की अनुमतियाँ बदलें
            fs.chmodSync(directory, 0o700);
        }
        
        // फ़ाइल सामग्री लिखें
        fs.writeFileSync(filePath, content, { 
            encoding: 'utf8',
            mode: 0o600  // केवल वर्तमान उपयोगकर्ता के लिए पढ़ने/लिखने की अनुमति
        });
        
        // सत्यापित करें कि फ़ाइल सफलतापूर्वक बनाई गई है
        if (fs.existsSync(filePath)) {
            const stats = fs.statSync(filePath);
            const fileMode = stats.mode & 0o777;
            
            // सुनिश्चित करें कि फ़ाइल अनुमतियाँ सही हैं (0o600)
            if (fileMode !== 0o600) {
                fs.chmodSync(filePath, 0o600);
            }
            
            return true;
        } else {
            throw new Error('फ़ाइल बनाने में विफल');
        }
    } catch (error) {
        console.error('गुप्त फ़ाइल सहेजने में त्रुटि:', error.message);
        throw error;
    }
}