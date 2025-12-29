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
    const url = new URL(target);
    const targetDomain = url.hostname;

    if (targetDomain.endsWith(domain)) {
        return target;
    }

    return `https://${domain}`;
}