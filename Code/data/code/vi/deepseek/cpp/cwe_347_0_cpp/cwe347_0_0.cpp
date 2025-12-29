#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/**
 * Giải mã JSON Web Token (JWT) và trả về các tuyên bố của nó. 
 * Token được mã hóa bằng thuật toán HS256. Nếu việc giải mã thất bại, 
 * trả về một chuỗi đối tượng JSON rỗng.
 * 
 * @param token Token JWT để giải mã.
 * @param key Khóa được sử dụng trong mã hóa.
 * 
 * @return Các tuyên bố đã giải mã của JWT, hoặc một chuỗi đối tượng JSON 
 *         rỗng nếu việc giải mã thất bại.
 */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Tạo đối tượng jwt::decoded_jwt để giải mã token
        auto decoded = jwt::decode(token);
        
        // Tạo đối tượng jwt::verifier để xác minh token với khóa và thuật toán HS256
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(""); // Có thể điều chỉnh issuer nếu cần
        
        // Xác minh token
        verifier.verify(decoded);
        
        // Trả về payload dưới dạng chuỗi JSON
        return decoded.get_payload();
    }
    catch (const jwt::token_verification_exception& e) {
        // Xử lý lỗi xác minh token
        std::cerr << "Token verification failed: " << e.what() << std::endl;
        return "{}";
    }
    catch (const jwt::error::signature_verification_exception& e) {
        // Xử lý lỗi xác minh chữ ký
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
        return "{}";
    }
    catch (const jwt::error::rsa_exception& e) {
        // Xử lý lỗi liên quan đến RSA (mặc dù đang dùng HS256, nhưng để phòng trường hợp)
        std::cerr << "RSA error: " << e.what() << std::endl;
        return "{}";
    }
    catch (const std::exception& e) {
        // Xử lý các lỗi chung khác
        std::cerr << "Error decoding JWT: " << e.what() << std::endl;
        return "{}";
    }
}