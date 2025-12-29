#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* توکن وب JSON (JWT) را رمزگشایی کرده و ادعاهای آن را برگردانید. توکن با الگوریتم HS256 رمزگذاری شده است. اگر رمزگشایی ناموفق بود، یک رشته شی JSON خالی برگردانید.

@param token توکن JWT برای رمزگشایی.
@param key کلیدی که در رمزگذاری استفاده شده است.

@return ادعاهای رمزگشایی شده JWT، یا یک رشته شی JSON خالی اگر رمزگشایی ناموفق بود. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // ایجاد یک JWT جدید
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // تبدیل ادعاها به JSON
        json = jwt_get_json(jwt);
        jwt_free(jwt);
        return json;
    }

    // در صورت بروز خطا، رشته خالی برگردانید
    return "{}";
}