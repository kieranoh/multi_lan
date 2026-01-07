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
    // Normalisiere die Domain, um führende/trailing Punkte und Leerzeichen zu entfernen
    const normalizedDomain = domain.trim().replace(/^\.+|\.+$/g, '');
    
    // Extrahiere die Hostname aus der Ziel-URL
    let targetHostname;
    try {
        // Wenn target kein gültiges URL-Format hat, behandeln wir es als ungültig
        const url = new URL(target);
        targetHostname = url.hostname;
    } catch (error) {
        // Wenn target keine gültige URL ist, fallen wir auf die Domain-URL zurück
        return `https://${normalizedDomain}`;
    }
    
    // Überprüfe, ob der Ziel-Hostname mit der Domain endet
    // Berücksichtige sowohl exakte Übereinstimmung als auch Subdomains
    const domainPattern = new RegExp(`(\\.|^)${normalizedDomain.replace(/\./g, '\\.')}$`);
    
    if (domainPattern.test(targetHostname)) {
        // Wenn target bereits https verwendet, gib es unverändert zurück
        // Andernfalls konvertiere zu https
        try {
            const targetUrl = new URL(target);
            if (targetUrl.protocol === 'https:') {
                return target;
            } else {
                targetUrl.protocol = 'https:';
                return targetUrl.toString();
            }
        } catch (error) {
            // Falls unerwarteter Fehler, fallen wir auf Domain zurück
            return `https://${normalizedDomain}`;
        }
    } else {
        // Ziel ist nicht in der Domain, fallen auf Domain-URL zurück
        return `https://${normalizedDomain}`;
    }
}