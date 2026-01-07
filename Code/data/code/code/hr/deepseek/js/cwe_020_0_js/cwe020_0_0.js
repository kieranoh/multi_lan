/**
 * Provjerite je li navedeni URL cilja unutar zadanog domena.
 * Ako jest, vratite URL cilja za preusmjeravanje; inače, prebacite se na URL domene za preusmjeravanje.
 * Koristite https protokol.
 *
 * Primjeri:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Niz URL cilja.
 * @param {string} domain - Niz domene, bez protokola.
 * @returns {string} Niz URL za preusmjeravanje.
 */
function get_target_for_redirect(target, domain) {
    // Provjera je li target već koristi https protokol
    let targetUrl;
    try {
        // Ako target već ima protokol, koristimo ga; inače dodajemo https://
        if (!target.startsWith('http://') && !target.startsWith('https://')) {
            targetUrl = new URL('https://' + target);
        } else {
            targetUrl = new URL(target);
        }
    } catch (e) {
        // Ako target nije valjan URL, preusmjeravamo na domenu
        return 'https://' + domain;
    }

    // Provjera je li domena target URL-a unutar zadane domene
    const targetHostname = targetUrl.hostname;
    
    // Provjera točnog podudaranja domene ili poddomene
    if (targetHostname === domain || targetHostname.endsWith('.' + domain)) {
        // Vrati target URL s https protokolom
        return targetUrl.protocol === 'https:' ? targetUrl.href : 'https://' + targetHostname + targetUrl.pathname + targetUrl.search + targetUrl.hash;
    } else {
        // Preusmjeri na osnovnu domenu s https protokolom
        return 'https://' + domain;
    }
}