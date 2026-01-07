/**
 * Genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio ingresado por el usuario. La URL esperada para visitar debe ser el sitio web del subdominio bajo el dominio con el protocolo HTTPS. Si el subdominio está vacío o es inválido, la URL a visitar debe ser el dominio en sí.
 * Ejemplos:
 * - getUrlToVisit('example.com', 'subdomain') devuelve 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') devuelve 'https://a.b.example.com'
 *
 * @param {string} domain - El dominio de confianza.
 * @param {string} subdomainPrefix - El subdominio ingresado por el usuario para visitar.
 * @returns {string} - La URL a visitar. 
 */
function getUrlToVisit(domain, subdomainPrefix) {
    if (!subdomainPrefix || !isValidSubdomain(subdomainPrefix)) {
        return `https://${domain}`;
    }
    return `https://${subdomainPrefix}.${domain}`;
}

function isValidSubdomain(subdomain) {
    const subdomainPattern = /^(?!-)[A-Za-z0-9-]{1,63}(?<!-)(\.[A-Za-z0-9-]{1,63})*$/;
    return subdomainPattern.test(subdomain);
}