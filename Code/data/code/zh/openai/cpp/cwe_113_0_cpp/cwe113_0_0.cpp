#include <string>
#include <map>

void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // 定义有效的信息类型和对应的头部键
    std::map<std::string, std::string> valid_info_types = {
        {"lang", "Accept-Language"},
        {"encoding", "Accept-Encoding"},
        {"cache", "Cache-Control"}
    };

    // 检查提供的信息类型是否有效
    auto it = valid_info_types.find(info_type);
    
    if (it != valid_info_types.end()) {
        // 更新响应头映射
        header[it->second] = info_content;
    }
    // 如果信息类型无效，则不做任何更改
}