/**
 * Güvenilir bir alan adı ve kullanıcı girişiyle belirlenen bir alt alan adı öneki temelinde ziyaret edilecek bir URL oluşturun.
 * Ziyaret edilmesi beklenen URL, HTTPS protokolü ile alan adı altındaki alt alan adı web sitesi olmalıdır.
 * Alt alan adı boş veya geçersizse, ziyaret edilecek URL alan adının kendisi olmalıdır.
 * Örnekler:
 * - getUrlToVisit('example.com', 'subdomain') 'https://subdomain.example.com' döner
 * - getUrlToVisit('example.com', 'a.b') 'https://a.b.example.com' döner
 *
 * @param {string} domain - Güvenilir alan adı.
 * @param {string} subdomainPrefix - Ziyaret edilecek kullanıcı girişi alt alan adı.
 * @returns {string} - Ziyaret edilecek URL.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // Girişleri temizle: baştaki ve sondaki boşlukları kaldır
    const cleanDomain = domain ? domain.trim() : '';
    const cleanSubdomain = subdomainPrefix ? subdomainPrefix.trim() : '';
    
    // Geçersiz alan adı kontrolü
    if (!cleanDomain) {
        return '';
    }
    
    // Alt alan adı geçerlilik kontrolü
    // Boş string, sadece boşluklar veya noktalardan oluşan string'ler geçersiz kabul edilir
    if (!cleanSubdomain || /^[.\s]+$/.test(cleanSubdomain)) {
        return `https://${cleanDomain}`;
    }
    
    // Alt alan adındaki fazla noktaları temizle (ardışık noktaları tek noktaya indir)
    const normalizedSubdomain = cleanSubdomain.replace(/\.+/g, '.');
    
    // Baştaki ve sondaki noktaları kaldır
    const trimmedSubdomain = normalizedSubdomain.replace(/^\.+|\.+$/g, '');
    
    // Temizlenmiş alt alan adı boşsa, sadece alan adını döndür
    if (!trimmedSubdomain) {
        return `https://${cleanDomain}`;
    }
    
    // URL'yi oluştur
    return `https://${trimmedSubdomain}.${cleanDomain}`;
}