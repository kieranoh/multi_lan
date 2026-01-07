#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // 辅助函数：将字符串转换为小写
    auto to_lower = [](std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    };

    // 辅助函数：检查字符串是否以指定后缀结尾
    auto ends_with = [](const std::string& str, const std::string& suffix) {
        if (suffix.size() > str.size()) return false;
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
    };

    // 辅助函数：从URL中提取主机名
    auto extract_hostname = [](const std::string& url) -> std::string {
        // 查找协议分隔符
        size_t protocol_end = url.find("://");
        if (protocol_end == std::string::npos) {
            // 如果没有协议，假设整个字符串是主机名
            return url;
        }
        
        // 跳过协议部分
        size_t host_start = protocol_end + 3;
        
        // 查找路径开始位置
        size_t path_start = url.find('/', host_start);
        
        // 提取主机名（可能包含端口）
        std::string hostname;
        if (path_start == std::string::npos) {
            hostname = url.substr(host_start);
        } else {
            hostname = url.substr(host_start, path_start - host_start);
        }
        
        return hostname;
    };

    // 辅助函数：从主机名中提取域名（移除端口和子域名）
    auto extract_domain_from_hostname = [](const std::string& hostname) -> std::string {
        // 移除端口号
        size_t port_pos = hostname.find(':');
        std::string host_without_port = (port_pos == std::string::npos) ? 
                                        hostname : hostname.substr(0, port_pos);
        
        // 查找最后一个点之后的部分（顶级域名和可能的二级域名）
        size_t last_dot = host_without_port.find_last_of('.');
        if (last_dot == std::string::npos) {
            return host_without_port;  // 没有点，可能是本地主机名
        }
        
        // 查找倒数第二个点，以获取完整的域名
        size_t second_last_dot = host_without_port.substr(0, last_dot).find_last_of('.');
        
        if (second_last_dot == std::string::npos) {
            // 只有一个点，返回整个主机名
            return host_without_port;
        } else {
            // 返回最后两部分（如 example.com）
            return host_without_port.substr(second_last_dot + 1);
        }
    };

    // 将输入转换为小写以进行不区分大小写的比较
    std::string target_lower = to_lower(target);
    std::string domain_lower = to_lower(domain);
    
    // 从目标URL中提取主机名
    std::string target_hostname = extract_hostname(target_lower);
    
    // 从主机名中提取域名
    std::string target_domain = extract_domain_from_hostname(target_hostname);
    
    // 检查目标域名是否与提供的域名匹配
    if (target_domain == domain_lower) {
        // 确保返回的URL使用https协议
        if (target_lower.find("https://") == 0) {
            return target;  // 已经是https，直接返回
        } else if (target_lower.find("http://") == 0) {
            // 将http替换为https
            return "https" + target.substr(4);
        } else {
            // 没有协议，添加https://
            return "https://" + target;
        }
    } else {
        // 域名不匹配，回退到域URL
        return "https://" + domain;
    }
}