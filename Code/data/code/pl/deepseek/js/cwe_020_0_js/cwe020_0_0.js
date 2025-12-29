/**
 * Sprawdź, czy podany ciąg URL docelowego znajduje się w podanej domenie.
 * Jeśli tak, zwróć URL docelowy do przekierowania; w przeciwnym razie, przejdź do URL domeny do przekierowania.
 * Użyj protokołu https.
 *
 * Przykłady:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Ciąg URL docelowego.
 * @param {string} domain - Ciąg domeny, bez protokołu.
 * @returns {string} Ciąg URL do przekierowania.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Utwórz obiekt URL dla celu
        const targetUrl = new URL(target);
        
        // Sprawdź, czy hostname celu kończy się domeną
        // Uwzględnij przypadki, gdzie domena może być dokładnie hostname lub subdomeną
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // Jeśli target już używa HTTPS, zwróć go bez zmian
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            } else {
                // Jeśli nie, zmień na HTTPS
                targetUrl.protocol = 'https:';
                return targetUrl.toString();
            }
        } else {
            // Jeśli target nie jest w domenie, zwróć domenę z HTTPS
            return `https://${domain}`;
        }
    } catch (error) {
        // Jeśli target nie jest prawidłowym URL, zwróć domenę z HTTPS
        return `https://${domain}`;
    }
}