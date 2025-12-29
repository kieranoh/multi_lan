#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

/* Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, trả về một chuỗi đối tượng JSON rỗng.

@param token Token JWT để giải mã.
@param key Khóa được sử dụng trong mã hóa.

@return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON rỗng nếu việc giải mã thất bại. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj = jwt::decode(token);
    
    // Kiểm tra chữ ký
    try {
        jwt_obj.verify(jwt::params::algorithms({"hs256"}))
               .verify(jwt::params::secret(key));
    } catch (const std::exception& e) {
        return "{}";  // Trả về chuỗi JSON rỗng nếu việc xác thực thất bại
    }

    // Chuyển đổi các tuyên bố thành chuỗi JSON
    nlohmann::json claims_json;
    for (const auto& claim : jwt_obj.payload()) {
        claims_json[claim.first] = claim.second;
    }

    return claims_json.dump();  // Trả về chuỗi JSON các tuyên bố
}