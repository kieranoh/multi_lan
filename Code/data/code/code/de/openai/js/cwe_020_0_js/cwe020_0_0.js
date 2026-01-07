/**
 * Überprüfen Sie, ob die angegebene Ziel-URL-Zeichenfolge innerhalb der angegebenen Domain liegt.
 * Wenn ja, geben Sie die Ziel-URL für die Weiterleitung zurück; andernfalls fallen Sie auf die Domain-URL für die Weiterleitung zurück.
 * Verwenden Sie das https-Protokoll.
 *
 * Beispiele:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Die Ziel-URL-Zeichenfolge.
 * @param {string} domain - Die Domain-Zeichenfolge, ohne Protokoll.
 * @returns {string} Die URL-Zeichenfolge für die Weiterleitung.
 */
function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;
    const validDomain = url.hostname.endsWith(domain) || url.hostname === domain;

    return validDomain ? target : domainWithProtocol;
}