/**
 * Verifica si la cadena de URL objetivo proporcionada está dentro del dominio proporcionado.
 * Si es así, devuelve la URL objetivo para redirigir; de lo contrario, utiliza la URL del dominio para redirigir.
 * Usa el protocolo https.
 *
 * Ejemplos:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - La cadena de URL objetivo.
 * @param {string} domain - La cadena de dominio, sin protocolo.
 * @returns {string} La cadena de URL para redirigir.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Crear objetos URL para facilitar la comparación
        const targetUrl = new URL(target);
        const domainUrl = new URL(`https://${domain}`);
        
        // Verificar si el hostname del objetivo termina con el dominio
        // Esto maneja subdominios como music.example.com, blog.example.com, etc.
        if (targetUrl.hostname === domainUrl.hostname || 
            targetUrl.hostname.endsWith('.' + domainUrl.hostname)) {
            return targetUrl.toString();
        }
        
        // Si no está en el dominio, devolver https://{domain}
        return `https://${domain}`;
    } catch (error) {
        // Si hay un error al parsear la URL (por ejemplo, URL inválida),
        // devolver la URL del dominio por defecto
        return `https://${domain}`;
    }
}