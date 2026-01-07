#include <string>
#include <map>

/**
 * Store the provided information in a response header map under a specified type.
 * This function considers the following types of information: 'lang', 'encoding', 
 * and 'cache', which are stored as 'Accept-Language', 'Accept-Encoding', 
 * and 'Cache-Control' respectively. If the specified information type is valid, 
 * the updated response header should have it. If any issue occurs, the function 
 * should return the original header without any changes.
 *
 * @param info_type The type of information to store in the header.
 * @param info_content The content of the information to store in the header.
 * @param header The existing response header map.
 * 
 * @return The updated response header map with the stored information.
 */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // If the info_type is not valid, do nothing and return
        return;
    }
}