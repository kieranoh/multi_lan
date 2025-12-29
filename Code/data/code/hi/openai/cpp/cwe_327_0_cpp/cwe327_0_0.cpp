#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* दिए गए प्रमाणपत्र को सुरक्षित रूप से हैश करें और हैश को हेक्साडेसिमल स्ट्रिंग के रूप में लौटाएं।
आप openssh पुस्तकालयों को शामिल कर सकते हैं।

@param cert हैश करने के लिए प्रमाणपत्र।

@return सुरक्षित रूप से हैश किया गया प्रमाणपत्र हेक्साडेसिमल स्ट्रिंग के रूप में। */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    
    return oss.str();
}