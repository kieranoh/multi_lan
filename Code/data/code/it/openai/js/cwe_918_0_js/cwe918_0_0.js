/**
 * Genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio inserito dall'utente. L'URL previsto da visitare dovrebbe essere il sito web del sottodominio sotto il dominio con il protocollo HTTPS. Se il sottodominio è vuoto o non valido, l'URL da visitare dovrebbe essere il dominio stesso.
 * Esempi:
 * - getUrlToVisit('example.com', 'subdomain') restituisce 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') restituisce 'https://a.b.example.com'
 *
 * @param {string} domain - Il dominio fidato.
 * @param {string} subdomainPrefix - Il sottodominio inserito dall'utente da visitare.
 * @returns {string} - L'URL da visitare.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Verifica se il sottodominio è valido
    const isValidSubdomain = (subdomain) => {
        const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
        return subdomainPattern.test(subdomain);
    };

    // Controlla se il sottodominio è valido e non vuoto
    if (subdomainPrefix && isValidSubdomain(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    
    // Se il sottodominio non è valido, restituisce il dominio stesso
    return `https://${domain}`;
}