/**
 * Proverite da li je dati URL string cilja unutar datog domena.
 * Ako jeste, vratite URL cilja za preusmeravanje; u suprotnom, pređite na URL domena za preusmeravanje.
 * Koristite https protokol.
 *
 * Primeri:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - URL string cilja.
 * @param {string} domain - String domena, bez protokola.
 * @returns {string} URL string za preusmeravanje. 
 */
function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const domainWithProtocol = `https://${domain}`;

    if (url.hostname.endsWith(domain) || url.href === domainWithProtocol) {
        return target;
    } else {
        return domainWithProtocol;
    }
}