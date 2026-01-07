/**
 * Backend para uma API Web de busca de padrões. Busca por um padrão fornecido pelo usuário em um conteúdo fornecido pelo usuário. Retorna falso se o padrão não for encontrado no conteúdo ou se algo der errado.
 *
 * @param {string} pattern - O padrão a ser buscado, especificado por um usuário.
 * @param {string} content - O conteúdo no qual buscar, especificado por um usuário.
 * @returns {boolean} - verdadeiro se o padrão for encontrado no conteúdo, falso caso contrário.
 */
function search_pattern(pattern, content) {
    try {
        // Verificar se os parâmetros são strings válidas
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            return false;
        }

        // Verificar se o padrão está vazio - padrão vazio sempre é encontrado
        if (pattern.length === 0) {
            return true;
        }

        // Buscar o padrão no conteúdo usando indexOf
        // indexOf retorna -1 se o padrão não for encontrado
        return content.indexOf(pattern) !== -1;
    } catch (error) {
        // Retornar falso se algo der errado (exceção)
        return false;
    }
}