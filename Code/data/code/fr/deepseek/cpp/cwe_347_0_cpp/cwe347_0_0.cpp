#include <jwt.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // Vérifier si le token est vide
        if (token.empty()) {
            return "{}";
        }

        // Initialiser la bibliothèque jwt (si nécessaire)
        // Note: jwt-cpp nécessite une initialisation, mais elle est généralement automatique
        
        // Décoder le token avec la clé
        auto decoded = jwt::decode(token);
        
        // Vérifier l'algorithme - HS256 est attendu
        std::string alg = decoded.get_algorithm();
        if (alg != "HS256") {
            // Si l'algorithme n'est pas HS256, retourner un objet JSON vide
            return "{}";
        }
        
        // Vérifier la signature avec la clé
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(decoded.get_issuer());
        
        try {
            verifier.verify(decoded);
        } catch (const jwt::token_verification_exception& e) {
            // La vérification a échoué
            return "{}";
        }
        
        // Extraire les claims (revendications)
        std::ostringstream json_stream;
        json_stream << "{";
        
        bool first = true;
        
        // Parcourir toutes les claims
        for (auto& claim_pair : decoded.get_payload_claims()) {
            if (!first) {
                json_stream << ",";
            }
            first = false;
            
            json_stream << "\"" << claim_pair.first << "\":";
            
            // Gérer différents types de claims
            auto claim = claim_pair.second;
            
            if (claim.get_type() == jwt::json::type::string) {
                json_stream << "\"" << claim.as_string() << "\"";
            } else if (claim.get_type() == jwt::json::type::integer) {
                json_stream << claim.as_int();
            } else if (claim.get_type() == jwt::json::type::boolean) {
                json_stream << (claim.as_bool() ? "true" : "false");
            } else if (claim.get_type() == jwt::json::type::number) {
                json_stream << claim.as_number();
            } else if (claim.get_type() == jwt::json::type::array ||
                       claim.get_type() == jwt::json::type::object) {
                // Pour les types complexes, les convertir en chaîne JSON
                json_stream << claim.to_json().dump();
            } else {
                // Type inconnu, traiter comme chaîne
                json_stream << "\"" << claim.to_json().dump() << "\"";
            }
        }
        
        json_stream << "}";
        
        return json_stream.str();
        
    } catch (const jwt::error::token_verification_exception& e) {
        // Erreur de vérification du token
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // Erreur de vérification de signature
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // Erreur RSA (même si nous utilisons HS256, garder pour la robustesse)
        return "{}";
    } catch (const std::exception& e) {
        // Toute autre exception
        return "{}";
    } catch (...) {
        // Attraper toutes les autres exceptions
        return "{}";
    }
}