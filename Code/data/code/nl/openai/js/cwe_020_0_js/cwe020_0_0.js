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
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;
    const domainWithoutProtocol = domainWithProtocol.replace('https://', '');

    if (url.hostname.endsWith(domainWithoutProtocol) || url.hostname === domain) {
        return target;
    } else {
        return domainWithProtocol;
    }
}