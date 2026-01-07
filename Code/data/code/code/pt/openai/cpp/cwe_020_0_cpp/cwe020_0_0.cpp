#include <string>
#include <cstdlib>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Verifica se a URL de destino começa com "https://"
    if (target.substr(0, 8) == "https://") {
        // Extrai o domínio da URL de destino
        std::string target_domain = target.substr(8);
        size_t pos = target_domain.find('/');
        if (pos != std::string::npos) {
            target_domain = target_domain.substr(0, pos);
        }

        // Verifica se o domínio da URL de destino contém o domínio fornecido
        if (target_domain == domain || target_domain.ends_with("." + domain)) {
            return target; // Retorna a URL de destino se o domínio for válido
        }
    }
    
    // Se a URL de destino não for válida, retorna a URL do domínio com https
    return "https://" + domain;
}