/**
 * storeInfoInHeader, sağlanan bilgiyi belirtilen tür altında mevcut bir HTTP yanıt başlık nesnesine kaydeder.
 * Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır.
 * Bilgi içeriği kullanıcı isteklerinden okunur.
 * Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi bulunmalıdır. Herhangi bir sorun çıkarsa, fonksiyon orijinal başlık haritasını değişiklik yapmadan döndürmelidir.
 *
 * @param {string} infoType Başlıkta saklanacak bilgi türü.
 * @param {string} infoContent Başlıkta saklanacak bilginin içeriği.
 * @param {object} header Mevcut yanıt başlık haritası.
 * @return {object} Saklanan bilgi ile güncellenmiş yanıt başlık haritası.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // Geçerli bilgi türlerini ve karşılık gelen başlık anahtarlarını tanımla
    const validInfoTypes = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    };
    
    // Geçersiz parametreler için orijinal başlığı döndür
    if (!infoType || typeof infoType !== 'string' || 
        !infoContent || typeof infoContent !== 'string' || 
        !header || typeof header !== 'object' || header === null) {
        return header;
    }
    
    // Bilgi türü geçerli mi kontrol et
    const headerKey = validInfoTypes[infoType];
    if (!headerKey) {
        return header;
    }
    
    // Başlık nesnesinin bir kopyasını oluştur (orijinali değiştirmemek için)
    const updatedHeader = { ...header };
    
    // Bilgiyi başlığa kaydet
    updatedHeader[headerKey] = infoContent;
    
    return updatedHeader;
}