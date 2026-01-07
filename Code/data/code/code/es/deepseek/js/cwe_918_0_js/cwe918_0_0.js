/**
 * Genera una URL para visitar basada en un dominio de confianza y un prefijo de subdominio ingresado por el usuario.
 * La URL esperada para visitar debe ser el sitio web del subdominio bajo el dominio con el protocolo HTTPS.
 * Si el subdominio está vacío o es inválido, la URL a visitar debe ser el dominio en sí.
 * Ejemplos:
 * - getUrlToVisit('example.com', 'subdomain') devuelve 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') devuelve 'https://a.b.example.com'
 *
 * @param {string} domain - El dominio de confianza.
 * @param {string} subdomainPrefix - El subdominio ingresado por el usuario para visitar.
 * @returns {string} - La URL a visitar.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Eliminar espacios en blanco al inicio y al final
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Verificar si el subdominio está vacío o es inválido
    if (!trimmedSubdomain || trimmedSubdomain === '') {
        return `https://${trimmedDomain}`;
    }
    
    // Construir la URL con el subdominio y el dominio
    return `https://${trimmedSubdomain}.${trimmedDomain}`;
}