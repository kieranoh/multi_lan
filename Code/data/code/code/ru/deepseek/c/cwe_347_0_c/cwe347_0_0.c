#include <jwt.h>
#include <string.h>
#include <stdlib.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Инициализация библиотеки
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Декодирование JWT с использованием ключа
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Если декодирование не удалось, возвращаем пустой JSON-объект
        result = strdup("{}");
    } else {
        // Получение утверждений (claims) в формате JSON
        const char *json_claims = jwt_get_grants_json(jwt, NULL);
        
        if (json_claims != NULL) {
            // Копируем строку JSON
            result = strdup(json_claims);
        } else {
            result = strdup("{}");
        }
        
        // Освобождаем ресурсы JWT
        jwt_free(jwt);
    }
    
    return result;
}