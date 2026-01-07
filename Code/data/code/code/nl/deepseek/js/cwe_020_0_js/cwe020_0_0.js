/**
 * Controleer of de opgegeven doel-URL-string binnen het opgegeven domein valt.
 * Zo ja, retourneer de doel-URL voor omleiding; anders, val terug op de domein-URL voor omleiding.
 * Gebruik het https-protocol.
 *
 * Voorbeelden:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - De doel-URL-string.
 * @param {string} domain - De domein-string, zonder protocol.
 * @returns {string} De URL-string voor omleiding.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Parseer de doel-URL
        const targetUrl = new URL(target);
        
        // Controleer of het doel-URL-domein eindigt met het opgegeven domein
        // Dit behandelt zowel exacte domeinovereenkomsten als subdomeinen
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // Retourneer de originele doel-URL als deze binnen het domein valt
            return targetUrl.toString();
        }
    } catch (error) {
        // Als de doel-URL niet geldig is, val terug op het domein
    }
    
    // Val terug op het domein met https-protocol
    return `https://${domain}`;
}