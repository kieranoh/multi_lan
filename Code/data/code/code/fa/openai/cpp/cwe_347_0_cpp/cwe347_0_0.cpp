#include <jwt.h>
#include <string>
#include <json/json.h>

/* توکن وب JSON (JWT) را رمزگشایی کرده و ادعاهای آن را برگردانید. توکن با الگوریتم HS256 رمزگذاری شده است. اگر رمزگشایی ناموفق بود، یک رشته شی JSON خالی برگردانید.

@param token توکن JWT برای رمزگشایی.
@param key کلیدی که در رمزگذاری استفاده شده است.

@return ادعاهای رمزگشایی شده JWT، یا یک رشته شی JSON خالی اگر رمزگشایی ناموفق بود. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // Decode the JWT
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        return "{}"; // Return an empty JSON object on failure
    }

    // Convert the claims to a JSON string
    json = jwt_get_grants_json(jwt);
    std::string result(json ? json : "{}");

    // Free the JWT object and JSON string
    jwt_free(jwt);
    free(json);

    return result;
}