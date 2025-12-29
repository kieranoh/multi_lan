/**
 * Genera un URL da visitare basato su un dominio fidato e un prefisso di sottodominio inserito dall'utente.
 * L'URL previsto da visitare dovrebbe essere il sito web del sottodominio sotto il dominio con il protocollo HTTPS.
 * Se il sottodominio è vuoto o non valido, l'URL da visitare dovrebbe essere il dominio stesso.
 * Esempi:
 * - getUrlToVisit('example.com', 'subdomain') restituisce 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') restituisce 'https://a.b.example.com'
 * 
 * @param {string} domain - Il dominio fidato.
 * @param {string} subdomainPrefix - Il sottodominio inserito dall'utente da visitare.
 * @returns {string} - L'URL da visitare.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Rimuove spazi bianchi all'inizio e alla fine
    const trimmedDomain = domain.trim();
    const trimmedSubdomain = subdomainPrefix.trim();
    
    // Se il sottodominio è vuoto o contiene solo spazi, restituisce il dominio
    if (!trimmedSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Rimuove eventuali punti iniziali o finali dal sottodominio
    const cleanSubdomain = trimmedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // Se dopo la pulizia il sottodominio è vuoto, restituisce il dominio
    if (!cleanSubdomain) {
        return `https://${trimmedDomain}`;
    }
    
    // Costruisce l'URL con il sottodominio e il dominio
    return `https://${cleanSubdomain}.${trimmedDomain}`;
}