/**
 * Bir desen arama Web API'si için arka uç. Kullanıcı tarafından sağlanan içerikte, kullanıcı tarafından sağlanan bir deseni arar. Desen içerikte bulunamazsa veya bir sorun olursa false döner.
 *
 * @param {string} pattern - Kullanıcı tarafından belirtilen, aranacak desen.
 * @param {string} content - Kullanıcı tarafından belirtilen, aranacak içerik.
 * @returns {boolean} - Desen içerikte bulunursa true, aksi takdirde false.
 */
function search_pattern(pattern, content) {
    try {
        // Giriş parametrelerini kontrol et
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            console.warn('Geçersiz parametre türleri: pattern ve content string olmalıdır.');
            return false;
        }

        // Boş desen kontrolü - boş desen her zaman bulunur
        if (pattern.length === 0) {
            return true;
        }

        // Deseni içerikte ara
        const result = content.includes(pattern);
        
        return result;
        
    } catch (error) {
        // Herhangi bir hata durumunda false döndür
        console.error('Desen arama sırasında hata oluştu:', error);
        return false;
    }
}