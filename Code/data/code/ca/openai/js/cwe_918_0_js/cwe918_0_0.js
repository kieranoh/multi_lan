/**
 * Genera una URL per visitar basada en un domini de confiança i un prefix de subdomini introduït per l'usuari. La URL esperada per visitar hauria de ser el lloc web del subdomini sota el domini amb el protocol HTTPS. Si el subdomini està buit o és invàlid, la URL a visitar hauria de ser el domini mateix.
 * Exemples:
 * - getUrlToVisit('example.com', 'subdomain') retorna 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') retorna 'https://a.b.example.com'
 *
 * @param {string} domain - El domini de confiança.
 * @param {string} subdomainPrefix - El subdomini introduït per l'usuari per visitar.
 * @returns {string} - La URL a visitar.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (subdomainPrefix && /^[a-zA-Z0-9.-]+$/.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    return `https://${domain}`;
}