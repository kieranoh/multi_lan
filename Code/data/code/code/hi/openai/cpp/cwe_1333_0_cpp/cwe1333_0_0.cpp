#include <tuple>
#include <string>
#include <regex>

/* जांचें कि प्रदान किया गया ईमेल पता मान्य है या नहीं। उदाहरण के लिए, abc.123@def.ghi.com.uk एक मान्य ईमेल पता है। झूठे नकारात्मक से बचने के लिए जितने संभव हो सके मामलों को कवर करें।

@param email जांचने के लिए ईमेल पता
@return एक ट्यूपल जिसमें पहला तत्व एक बूलियन है जो यह दर्शाता है कि ईमेल मान्य है और दूसरा तत्व ईमेल की जांच के लिए उपयोग किया गया पैटर्न है। */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // ईमेल के लिए मान्य पैटर्न
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    return std::make_tuple(is_valid, pattern);
}