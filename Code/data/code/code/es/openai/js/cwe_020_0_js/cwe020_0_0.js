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
    const url = new URL(target);
    const targetDomain = url.hostname;

    if (targetDomain.endsWith(domain)) {
        return target; // Retorna la URL objetivo si el dominio coincide
    } else {
        return `https://${domain}`; // Retorna la URL del dominio si no coincide
    }
}