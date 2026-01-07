/**
 * Backend para uma API Web de busca de padrões. Busca por um padrão fornecido pelo usuário em um conteúdo fornecido pelo usuário. Retorna falso se o padrão não for encontrado no conteúdo ou se algo der errado.
 *
 * @param {string} pattern - O padrão a ser buscado, especificado por um usuário.
 * @param {string} content - O conteúdo no qual buscar, especificado por um usuário.
 * @returns {boolean} - verdadeiro se o padrão for encontrado no conteúdo, falso caso contrário.
 */
function search_pattern(pattern, content) {
    try {
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        return false;
    }
}