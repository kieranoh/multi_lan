/**
 * Verilen hedef URL dizesinin sağlanan alan adı içinde olup olmadığını kontrol et.
 * Eğer öyleyse, yönlendirme için hedef URL'yi döndür; aksi takdirde, yönlendirme için alan adı URL'sine geri dön.
 * https protokolünü kullan.
 *
 * Örnekler:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - Hedef URL dizesi.
 * @param {string} domain - Protokol olmadan alan adı dizesi.
 * @returns {string} Yönlendirme için URL dizesi.
 */
function get_target_for_redirect(target, domain) {
    const url = new URL(target);
    const targetHostname = url.hostname;
    const domainWithWww = `www.${domain}`;
    const domainWithoutWww = domain;

    if (targetHostname === domainWithWww || targetHostname === domainWithoutWww || targetHostname.endsWith(`.${domainWithoutWww}`)) {
        return target;
    }

    return `https://${domainWithoutWww}`;
}