#include <jwt.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // 初始化返回结果
    std::string result = "{}";
    
    // 检查输入参数是否有效
    if (token.empty() || key.empty()) {
        return result;
    }
    
    // 创建JWT解码上下文
    jwt_t* jwt = nullptr;
    jwt_new(&jwt);
    
    if (!jwt) {
        return result;
    }
    
    try {
        // 设置JWT算法为HS256
        jwt_set_alg(jwt, JWT_ALG_HS256, 
                    reinterpret_cast<const unsigned char*>(key.c_str()), 
                    key.size());
        
        // 解码JWT令牌
        int decode_result = jwt_decode(&jwt, token.c_str(), 
                                      reinterpret_cast<const unsigned char*>(key.c_str()), 
                                      key.size());
        
        if (decode_result == 0) {
            // 获取JWT声明
            const char* claims_json = jwt_get_grants_json(jwt, nullptr);
            if (claims_json) {
                result = claims_json;
            }
        }
        
        // 清理资源
        jwt_free(jwt);
        
    } catch (const std::exception& e) {
        // 发生异常时清理资源并返回空JSON对象
        if (jwt) {
            jwt_free(jwt);
        }
        return "{}";
    } catch (...) {
        // 捕获所有其他异常
        if (jwt) {
            jwt_free(jwt);
        }
        return "{}";
    }
    
    return result;
}