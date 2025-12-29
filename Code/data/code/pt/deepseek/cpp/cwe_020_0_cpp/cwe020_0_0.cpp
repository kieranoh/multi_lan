#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // Função auxiliar para converter para minúsculas
    auto to_lower = [](std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    };

    // Função auxiliar para extrair o host de uma URL
    auto extract_host = [](const std::string& url) -> std::string {
        // Encontrar a posição do protocolo
        size_t protocol_pos = url.find("://");
        if (protocol_pos == std::string::npos) {
            // Se não houver protocolo, assumir que a string já é um host
            return url;
        }
        
        // Extrair a parte após o protocolo
        std::string after_protocol = url.substr(protocol_pos + 3);
        
        // Encontrar a primeira barra ou fim da string
        size_t slash_pos = after_protocol.find('/');
        if (slash_pos == std::string::npos) {
            return after_protocol;
        }
        
        return after_protocol.substr(0, slash_pos);
    };

    // Função auxiliar para extrair o domínio do host (remover subdomínios)
    auto extract_base_domain = [](const std::string& host) -> std::string {
        // Encontrar a última ocorrência de ponto
        size_t last_dot = host.find_last_of('.');
        if (last_dot == std::string::npos) {
            return host;
        }
        
        // Encontrar o ponto anterior para domínios como .co.uk, .com.br, etc.
        // Esta é uma implementação simplificada que assume domínios de segundo nível
        size_t second_last_dot = host.substr(0, last_dot).find_last_of('.');
        if (second_last_dot == std::string::npos) {
            return host.substr(0, last_dot);
        }
        
        // Para domínios com múltiplas partes, pegar a partir do segundo último ponto
        return host.substr(second_last_dot + 1);
    };

    try {
        // Converter para minúsculas para comparação case-insensitive
        std::string target_lower = to_lower(target);
        std::string domain_lower = to_lower(domain);
        
        // Extrair o host da URL de destino
        std::string target_host = extract_host(target_lower);
        
        // Extrair o domínio base do host de destino
        std::string target_domain = extract_base_domain(target_host);
        
        // Verificar se o domínio base corresponde ao domínio fornecido
        if (target_domain == domain_lower) {
            // Se o alvo já começa com https, retornar como está
            if (target_lower.find("https://") == 0) {
                return target;
            }
            // Caso contrário, adicionar https://
            return "https://" + target;
        } else {
            // Retornar o domínio com https://
            return "https://" + domain;
        }
    } catch (...) {
        // Em caso de erro, retornar o domínio padrão com https
        return "https://" + domain;
    }
}