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
    try {
        // Crea oggetti URL per il target e per il dominio di base
        const targetUrl = new URL(target);
        const baseUrl = new URL(`https://${domain}`);
        
        // Controlla se l'hostname del target termina con il dominio specificato
        // Gestisce sia il dominio esatto che i sottodomini
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith(`.${domain}`)) {
            // Se il target è già https, restituiscilo così com'è
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            } else {
                // Altrimenti, converti a https mantenendo il resto dell'URL
                return `https://${targetUrl.hostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
            }
        } else {
            // Se il target non è nel dominio, restituisci l'URL di base con https
            return baseUrl.toString();
        }
    } catch (error) {
        // Se c'è un errore nella creazione degli URL (es. URL non valido),
        // restituisci l'URL di base con https
        return `https://${domain}`;
    }
}