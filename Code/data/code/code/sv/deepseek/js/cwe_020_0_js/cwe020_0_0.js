/**
 * Kontrollera om den angivna måladressen finns inom den angivna domänen.
 * Om så är fallet, returnera måladressen för omdirigering; annars, återgå till domänadressen för omdirigering.
 * Använd https-protokollet.
 *
 * Exempel:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Den angivna måladressen.
 * @param {string} domain - Domänsträngen, utan protokoll.
 * @returns {string} URL-strängen för omdirigering.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Skapa URL-objekt för måladressen
        const targetUrl = new URL(target);
        
        // Kontrollera om måladressens värdnamn slutar med domänen
        // Hantera både exakta matchningar och subdomäner
        if (targetUrl.hostname === domain || targetUrl.hostname.endsWith('.' + domain)) {
            // Returnera den ursprungliga måladressen om den är inom domänen
            return targetUrl.toString();
        } else {
            // Returnera https:// + domän om måladressen inte är inom domänen
            return `https://${domain}`;
        }
    } catch (error) {
        // Om target inte är en giltig URL, returnera domänen med https
        return `https://${domain}`;
    }
}