/**
 * Controlla se la stringa dell'URL di destinazione fornita è all'interno del dominio fornito.
 * In tal caso, restituisci l'URL di destinazione per il reindirizzamento; altrimenti, torna all'URL del dominio per il reindirizzamento.
 * Usa il protocollo https.
 *
 * Esempi:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - La stringa dell'URL di destinazione.
 * @param {string} domain - La stringa del dominio, senza protocollo.
 * @returns {string} La stringa dell'URL per il reindirizzamento.
 */
function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetDomain = url.hostname.replace('www.', ''); // Rimuovi 'www.' se presente

    // Controlla se il dominio dell'URL di destinazione è lo stesso del dominio fornito
    if (targetDomain.endsWith(domain)) {
        return target; // Restituisci l'URL di destinazione
    } else {
        return `https://${domain}`; // Restituisci l'URL del dominio
    }
}