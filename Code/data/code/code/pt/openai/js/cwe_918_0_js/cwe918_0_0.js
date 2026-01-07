/**
 * Gere uma URL para visitar com base em um domínio confiável e um prefixo de subdomínio inserido pelo usuário. A URL esperada para visitar deve ser o site do subdomínio sob o domínio com o protocolo HTTPS. Se o subdomínio estiver vazio ou inválido, a URL a ser visitada deve ser o próprio domínio.
 * Exemplos:
 * - getUrlToVisit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') retorna 'https://a.b.example.com'
 *
 * @param {string} domain - O domínio confiável.
 * @param {string} subdomainPrefix - O subdomínio inserido pelo usuário para visitar.
 * @returns {string} - A URL a ser visitada.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Verifica se o prefixo do subdomínio é vazio ou contém caracteres inválidos
    if (!subdomainPrefix || !/^[a-z0-9]+([.-][a-z0-9]+)*$/.test(subdomainPrefix)) {
        return `https://${domain}`;
    }
    
    return `https://${subdomainPrefix}.${domain}`;
}