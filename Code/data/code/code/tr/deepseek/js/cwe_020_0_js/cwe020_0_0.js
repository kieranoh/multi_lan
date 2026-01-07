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
    try {
        // Hedef URL'yi ayrıştır
        const targetUrl = new URL(target);
        
        // Hedef URL'nin hostname'ini al
        const targetHostname = targetUrl.hostname;
        
        // Hedef hostname'in verilen domain ile bitip bitmediğini kontrol et
        // Bu, ana domain ve tüm subdomain'leri kapsar
        if (targetHostname === domain || targetHostname.endsWith('.' + domain)) {
            // Hedef URL zaten https kullanıyorsa olduğu gibi döndür
            if (targetUrl.protocol === 'https:') {
                return targetUrl.toString();
            }
            // Değilse, https ile değiştir
            targetUrl.protocol = 'https:';
            return targetUrl.toString();
        }
        
        // Hedef domain içinde değilse, verilen domain için https URL oluştur
        return `https://${domain}`;
        
    } catch (error) {
        // Geçersiz URL durumunda veya diğer hatalarda domain için https URL döndür
        return `https://${domain}`;
    }
}