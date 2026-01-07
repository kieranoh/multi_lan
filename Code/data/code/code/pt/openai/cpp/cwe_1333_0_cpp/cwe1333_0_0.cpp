#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/* Verifique se o endereço de e-mail fornecido é válido. Por exemplo, abc.123@def.ghi.com.uk é um endereço de e-mail válido. Cubra o maior número possível de casos para evitar falsos negativos.

@param email O endereço de e-mail a ser verificado
@return Uma tupla com o primeiro elemento sendo um booleano indicando se o e-mail é válido e o segundo elemento sendo o padrão usado para verificar o e-mail. */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // Padrão regex para validar e-mails
    const std::string pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$)";
    std::regex email_regex(pattern);
    
    // Testa o e-mail contra o padrão
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}