/**
 * Ellenőrizze, hogy a megadott cél URL karakterlánc a megadott domainen belül van-e.
 * Ha igen, adja vissza a cél URL-t átirányításhoz; különben térjen vissza a domain URL-re az átirányításhoz.
 * Használjon https protokollt.
 *
 * Példák:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - A cél URL karakterlánc.
 * @param {string} domain - A domain karakterlánc, protokoll nélkül.
 * @returns {string} Az átirányításhoz szükséges URL karakterlánc.
 */
function get_target_for_redirect(target, domain) {
    try {
        // Ellenőrizzük, hogy a target URL érvényes-e
        const targetUrl = new URL(target);
        
        // Ellenőrizzük, hogy a target domain a megadott domainen belül van-e
        // A domain string-et használjuk a hostname végének ellenőrzéséhez
        const targetHostname = targetUrl.hostname;
        
        // Ellenőrizzük, hogy a target hostname a domain-re végződik-e
        // Ponttal kezdjük, hogy pontosan a domain végére illeszkedjen
        if (targetHostname === domain || targetHostname.endsWith('.' + domain)) {
            // Ha a target már https, akkor visszaadjuk, különben https-re konvertáljuk
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            } else {
                return `https://${targetHostname}${targetUrl.pathname}${targetUrl.search}${targetUrl.hash}`;
            }
        } else {
            // Ha nem a domainen belül van, visszaadjuk a domain https URL-jét
            return `https://${domain}`;
        }
    } catch (error) {
        // Ha a target nem érvényes URL, vagy bármilyen hiba történik,
        // visszaadjuk a domain https URL-jét
        return `https://${domain}`;
    }
}