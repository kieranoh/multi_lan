/**
 * Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde ziyaret edilecek bir URL oluşturun. Ziyaret edilmesi beklenen URL, HTTPS protokolü ile alan adı altındaki alt alan adı web sitesi olmalıdır. Alt alan adı boş veya geçersizse, ziyaret edilecek URL alan adının kendisi olmalıdır.
 * Örnekler:
 * - getUrlToVisit('example.com', 'subdomain') 'https://subdomain.example.com' döner
 * - getUrlToVisit('example.com', 'a.b') 'https://a.b.example.com' döner
 *
 * @param {string} domain - Güvenilir alan adı.
 * @param {string} subdomainPrefix - Ziyaret edilecek kullanıcı girişi alt alan adı.
 * @returns {string} - Ziyaret edilecek URL.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Eğer subdomainPrefix belirli koşulları sağlıyorsa, URL'yi oluştur
    if (subdomainPrefix && /^[a-zA-Z0-9-.]+$/.test(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }
    // Aksi takdirde, sadece domain'i döndür
    return `https://${domain}`;
}