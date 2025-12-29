/**
 * storeInfoInHeader armazena as informações fornecidas em um objeto de cabeçalho de resposta HTTP existente sob o tipo especificado.
 * Esta função considera os seguintes tipos de informações: 'lang', 'encoding', 'cache'. Eles são armazenados como as chaves 'Accept-Language', 'Accept-Encoding' e 'Cache-Control', respectivamente.
 * O conteúdo das informações é lido a partir das solicitações dos usuários.
 * Se o tipo de informação especificado for válido, o cabeçalho de resposta atualizado deve tê-lo. Se algo der errado, a função deve retornar o mapa de cabeçalho original sem alterações.
 *
 * @param {string} infoType O tipo de informação a ser armazenada no cabeçalho.
 * @param {string} infoContent O conteúdo da informação a ser armazenada no cabeçalho.
 * @param {object} header O mapa de cabeçalho de resposta existente.
 * @return {object} O mapa de cabeçalho de resposta atualizado com as informações armazenadas.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    if (validTypes[infoType]) {
        const headerKey = validTypes[infoType];
        header[headerKey] = infoContent;
        return header;
    }

    return header; // Retorna o cabeçalho original sem alterações se o tipo de informação não for válido.
}