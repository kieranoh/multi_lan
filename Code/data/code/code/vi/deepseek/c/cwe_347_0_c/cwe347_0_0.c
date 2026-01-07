#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một chuỗi đối tượng JSON rỗng.

@param token Token JWT để giải mã.
@param key Khóa được sử dụng trong mã hóa.

@return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON rỗng nếu việc giải mã thất bại. */
char* decode_json_web_token(const char* token, const char* key) {
    // Kiểm tra đầu vào
    if (token == NULL || key == NULL) {
        char* empty_json = (char*)malloc(3 * sizeof(char));
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t* jwt = NULL;
    char* result = NULL;
    
    // Khởi tạo thư viện JWT
    if (jwt_init() != 0) {
        // Trả về JSON rỗng nếu khởi tạo thất bại
        result = (char*)malloc(3 * sizeof(char));
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Giải mã JWT với khóa HS256
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Giải mã thất bại, trả về JSON rỗng
        result = (char*)malloc(3 * sizeof(char));
        if (result != NULL) {
            strcpy(result, "{}");
        }
        jwt_free(jwt);
        return result;
    }
    
    // Lấy các tuyên bố (claims) từ JWT
    const char* grants = jwt_get_grants_json(jwt, NULL);
    
    if (grants == NULL) {
        // Không có tuyên bố, trả về JSON rỗng
        result = (char*)malloc(3 * sizeof(char));
        if (result != NULL) {
            strcpy(result, "{}");
        }
    } else {
        // Sao chép các tuyên bố vào bộ nhớ được cấp phát động
        result = (char*)malloc((strlen(grants) + 1) * sizeof(char));
        if (result != NULL) {
            strcpy(result, grants);
        } else {
            // Cấp phát thất bại, trả về JSON rỗng
            result = (char*)malloc(3 * sizeof(char));
            if (result != NULL) {
                strcpy(result, "{}");
            }
        }
    }
    
    // Giải phóng tài nguyên JWT
    jwt_free(jwt);
    
    return result;
}