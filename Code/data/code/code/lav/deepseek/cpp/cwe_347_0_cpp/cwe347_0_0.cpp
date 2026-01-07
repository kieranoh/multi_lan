#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Parse the token
        auto decoded = jwt::decode(token);
        
        // Verify the token using the provided key and HS256 algorithm
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(decoded.get_issuer());
        
        verifier.verify(decoded);
        
        // Extract claims and build JSON string
        std::ostringstream json_stream;
        json_stream << "{";
        
        bool first = true;
        for (auto& claim : decoded.get_payload_claims()) {
            if (!first) {
                json_stream << ",";
            }
            first = false;
            
            json_stream << "\"" << claim.first << "\":";
            
            // Handle different claim types
            if (claim.second.get_type() == jwt::json::type::string) {
                json_stream << "\"" << claim.second.as_string() << "\"";
            } else if (claim.second.get_type() == jwt::json::type::integer) {
                json_stream << claim.second.as_int();
            } else if (claim.second.get_type() == jwt::json::type::number) {
                json_stream << claim.second.as_number();
            } else if (claim.second.get_type() == jwt::json::type::boolean) {
                json_stream << (claim.second.as_bool() ? "true" : "false");
            } else if (claim.second.get_type() == jwt::json::type::array ||
                       claim.second.get_type() == jwt::json::type::object) {
                json_stream << claim.second.to_json();
            } else {
                // Fallback to string representation
                json_stream << "\"" << claim.second.to_json() << "\"";
            }
        }
        
        json_stream << "}";
        return json_stream.str();
        
    } catch (const jwt::token_verification_exception& e) {
        // Verification failed (invalid signature, expired, etc.)
        std::cerr << "Token verification failed: " << e.what() << std::endl;
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // Signature verification failed
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // RSA related error (though we're using HS256, keeping for completeness)
        std::cerr << "RSA error: " << e.what() << std::endl;
        return "{}";
    } catch (const jwt::error::token_invalid_exception& e) {
        // Token is invalid (malformed)
        std::cerr << "Invalid token: " << e.what() << std::endl;
        return "{}";
    } catch (const std::exception& e) {
        // Any other exception
        std::cerr << "Error decoding token: " << e.what() << std::endl;
        return "{}";
    }
}