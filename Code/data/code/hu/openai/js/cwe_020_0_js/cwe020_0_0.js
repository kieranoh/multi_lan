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
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;

    if (url.hostname === domain || url.hostname.endsWith(`.${domain}`)) {
        return target;
    } else {
        return domainWithProtocol;
    }
}