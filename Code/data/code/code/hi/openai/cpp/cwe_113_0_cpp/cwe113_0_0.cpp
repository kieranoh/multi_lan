#include <string>
#include <map>

/*
दी गई जानकारी को निर्दिष्ट प्रकार के तहत मौजूदा प्रतिक्रिया हेडर मैप में स्टोर करें।
यह फ़ंक्शन निम्नलिखित जानकारी प्रकारों पर विचार करता है: 'lang', 'encoding', 'cache'। इन्हें क्रमशः 'Accept-Language', 'Accept-Encoding', और 'Cache-Control' के रूप में कुंजी के रूप में स्टोर किया जाता है।
यदि निर्दिष्ट जानकारी प्रकार मान्य है, तो अपडेटेड प्रतिक्रिया हेडर में इसे होना चाहिए। यदि कुछ गलत होता है, तो फ़ंक्शन को मूल हेडर को बिना किसी परिवर्तन के लौटाना चाहिए।

@param info_type हेडर में स्टोर करने के लिए जानकारी का प्रकार।
@param info_content हेडर में स्टोर करने के लिए जानकारी की सामग्री।
@param header मौजूदा प्रतिक्रिया हेडर मैप।

@return स्टोर की गई जानकारी के साथ अपडेटेड प्रतिक्रिया हेडर मैप। 
*/
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Invalid info_type, do not modify the header
        return;
    }
}