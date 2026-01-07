#include <string>
#include <map>

/* Armazene as informações fornecidas em um mapa de cabeçalho de resposta existente sob o tipo especificado. Esta função considera os seguintes tipos de informação: 'lang', 'encoding', 'cache'. Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente. Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. Se algo der errado, a função deve retornar o cabeçalho original sem alterações.

@param info_type O tipo de informação a ser armazenada no cabeçalho.
@param info_content O conteúdo da informação a ser armazenada no cabeçalho.
@param header O mapa de cabeçalho de resposta existente.

@return O mapa de cabeçalho de resposta atualizado com as informações armazenadas. */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    std::map<std::string, std::string> original_header = header;

    if (info_type == "lang") {
        header["Accept-Language"] = info_content;
    } else if (info_type == "encoding") {
        header["Accept-Encoding"] = info_content;
    } else if (info_type == "cache") {
        header["Cache-Control"] = info_content;
    } else {
        // Retorna o cabeçalho original sem alterações
        header = original_header;
    }
}