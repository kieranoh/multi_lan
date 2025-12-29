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
    // Remove espaços em branco no início e no fim
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Verifica se o subdomínio é vazio ou inválido
    if (!trimmedSubdomain || trimmedSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Remove possíveis barras ou caracteres inválidos do início/fim do subdomínio
    let cleanSubdomain = trimmedSubdomain.replace(/^[./]+|[./]+$/g, '');
    
    // Se após limpeza o subdomínio ficar vazio, retorna apenas o domínio
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Constrói a URL com o subdomínio e domínio
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}