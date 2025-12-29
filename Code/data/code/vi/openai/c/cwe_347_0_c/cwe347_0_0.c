#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một chuỗi đối tượng JSON rỗng.

@param token Token JWT để giải mã.
@param key Khóa được sử dụng trong mã hóa.

@return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON rỗng nếu việc giải mã thất bại. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char* json_output = NULL;

    // Giải mã JWT
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Chuyển đổi các tuyên bố thành chuỗi JSON
        json_output = jwt_get_granted_claims(jwt);
        jwt_free(jwt);
        return json_output;
    } else {
        // Nếu giải mã thất bại, trả về chuỗi JSON rỗng
        return "{}";
    }
}