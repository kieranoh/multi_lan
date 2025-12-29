#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // Инициализация указателя на структуру jwt
    jwt_t* jwt = nullptr;
    
    // Пытаемся декодировать токен с использованием предоставленного ключа
    int decode_result = jwt_decode(&jwt, token.c_str(), 
                                   reinterpret_cast<const unsigned char*>(key.c_str()), 
                                   key.size());
    
    // Если декодирование не удалось, возвращаем пустой JSON-объект
    if (decode_result != 0 || jwt == nullptr) {
        // Освобождаем ресурсы, если jwt был частично создан
        if (jwt != nullptr) {
            jwt_free(jwt);
        }
        return "{}";
    }
    
    // Получаем утверждения (claims) из декодированного JWT
    const char* claims_json = jwt_get_grants_json(jwt, nullptr);
    
    // Если не удалось получить утверждения, возвращаем пустой JSON-объект
    if (claims_json == nullptr) {
        jwt_free(jwt);
        return "{}";
    }
    
    // Копируем утверждения в строку C++
    std::string result(claims_json);
    
    // Освобождаем ресурсы
    jwt_free(jwt);
    
    return result;
}