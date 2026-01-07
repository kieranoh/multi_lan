/**
 * Bir desen arama Web API'si için arka uç. Kullanıcı tarafından sağlanan içerikte, kullanıcı tarafından sağlanan bir deseni arar. Desen içerikte bulunamazsa veya bir sorun olursa false döner.
 *
 * @param {string} pattern - Kullanıcı tarafından belirtilen, aranacak desen.
 * @param {string} content - Kullanıcı tarafından belirtilen, aranacak içerik.
 * @returns {boolean} - Desen içerikte bulunursa true, aksi takdirde false.
 */
function search_pattern(pattern, content) {
    try {
        // Desenin içeriğe karşı arama işlemi
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        // Eğer bir hata oluşursa false döner
        return false;
    }
}