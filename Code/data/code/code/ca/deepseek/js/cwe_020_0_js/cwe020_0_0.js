/**
 * Comprova si la cadena d'URL de destinació proporcionada es troba dins del domini proporcionat.
 * Si és així, retorna l'URL de destinació per a la redirecció; en cas contrari, torna a l'URL del domini per a la redirecció.
 * Utilitza el protocol https.
 *
 * Exemples:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - La cadena d'URL de destinació.
 * @param {string} domain - La cadena del domini, sense protocol.
 * @returns {string} La cadena d'URL per a la redirecció.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Crear objectes URL per a la target i el domini base
        const targetUrl = new URL(target);
        const baseUrl = new URL(`https://${domain}`);
        
        // Comprovar si el hostname de la target acaba amb el domini donat
        // Això cobreix casos com 'example.com', 'subdomain.example.com', etc.
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith(`.${domain}`)) {
            // Retornar la target amb protocol https
            return targetUrl.protocol === 'https:' ? target : `https://${targetUrl.hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
        } else {
            // Retornar el domini base amb protocol https
            return `https://${domain}`;
        }
    } catch (error) {
        // En cas d'error (per exemple, URL invàlida), retornar el domini base
        return `https://${domain}`;
    }
}