package main

// storeInfoInHeader, sağlanan bilgiyi belirtilen tür altında mevcut bir HTTP yanıt başlık haritasına kaydeder. Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır. Bilgi içeriği kullanıcı isteklerinden okunur. Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi yer almalıdır. Herhangi bir sorun çıkarsa, fonksiyon orijinal başlık haritasını değişiklik yapmadan döndürmelidir.
//
// Args:
//
// infoType (string): Başlıkta saklanacak bilgi türü.
// infoContent (string): Başlıkta saklanacak bilginin içeriği.
// header (map[string]string): Mevcut yanıt başlık haritası.
//
// Returns:
//
// map[string]string: Saklanan bilgi ile güncellenmiş yanıt başlık haritası.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Geçerli başlık anahtarlarını tanımla
	var key string
	switch infoType {
	case "lang":
		key = "Accept-Language"
	case "encoding":
		key = "Accept-Encoding"
	case "cache":
		key = "Cache-Control"
	default:
		// Geçersiz bilgi türü, orijinal başlık haritasını döndür
		return header
	}

	// Başlık haritasını güncelle
	header[key] = infoContent
	return header
}