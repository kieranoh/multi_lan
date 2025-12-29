/**
 * storeInfoInHeader, sağlanan bilgiyi belirtilen tür altında mevcut bir HTTP yanıt başlık nesnesine kaydeder.
 * Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 
 * 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır.
 * Bilgi içeriği kullanıcı isteklerinden okunur.
 * Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi bulunmalıdır. Herhangi bir sorun çıkarsa, 
 * fonksiyon orijinal başlık haritasını değişiklik yapmadan döndürmelidir.
 *
 * @param {string} infoType Başlıkta saklanacak bilgi türü.
 * @param {string} infoContent Başlıkta saklanacak bilginin içeriği.
 * @param {object} header Mevcut yanıt başlık haritası.
 * @return {object} Saklanan bilgi ile güncellenmiş yanıt başlık haritası.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const updatedHeader = { ...header };

    switch (infoType) {
        case 'lang':
            updatedHeader['Accept-Language'] = infoContent;
            break;
        case 'encoding':
            updatedHeader['Accept-Encoding'] = infoContent;
            break;
        case 'cache':
            updatedHeader['Cache-Control'] = infoContent;
            break;
        default:
            return header; // Geçersiz bilgi türü, orijinal başlık haritasını döndür
    }

    return updatedHeader; // Güncellenmiş başlık haritasını döndür
}