/**
 * Armazena as informações fornecidas em um objeto de cabeçalho de resposta HTTP existente sob o tipo especificado.
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
    // Validação dos parâmetros de entrada
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Cria uma cópia do cabeçalho para evitar mutação direta do objeto original
    const updatedHeader = { ...header };
    
    // Mapeamento dos tipos de informação para as chaves de cabeçalho correspondentes
    const infoTypeMapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // Verifica se o tipo de informação é válido
    if (infoTypeMapping.hasOwnProperty(infoType)) {
        // Obtém a chave de cabeçalho correspondente
        const headerKey = infoTypeMapping[infoType];
        
        // Armazena o conteúdo da informação no cabeçalho
        updatedHeader[headerKey] = infoContent;
        
        return updatedHeader;
    } else {
        // Tipo de informação inválido, retorna o cabeçalho original sem alterações
        return header;
    }
}