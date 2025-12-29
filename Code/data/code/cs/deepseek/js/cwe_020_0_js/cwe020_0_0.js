/**
 * Zkontrolujte, zda je zadaný cílový URL řetězec v rámci zadané domény.
 * Pokud ano, vraťte cílovou URL pro přesměrování; jinak se přepněte na doménovou URL pro přesměrování.
 * Použijte protokol https.
 *
 * Příklady:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Cílový URL řetězec.
 * @param {string} domain - Řetězec domény, bez protokolu.
 * @returns {string} Řetězec URL pro přesměrování.
 */
function get_target_for_redirect(target, domain) {
    // Zkontrolujte, zda je cílový URL platný
    let targetUrl;
    try {
        targetUrl = new URL(target);
    } catch (error) {
        // Pokud cílový URL není platný, vraťte doménu s https
        return `https://${domain}`;
    }

    // Zkontrolujte, zda cílový hostname končí zadanou doménou
    const targetHostname = targetUrl.hostname;
    
    // Kontrola, zda hostname přesně odpovídá doméně nebo je její subdoménou
    if (targetHostname === domain || targetHostname.endsWith(`.${domain}`)) {
        // Vraťte původní cílový URL
        return targetUrl.toString();
    } else {
        // Vraťte doménu s https protokolem
        return `https://${domain}`;
    }
}