package main

import (
	"strings"
)

// storeInfoInHeader, sağlanan bilgiyi belirtilen tür altında mevcut bir HTTP yanıt başlık haritasına kaydeder. Bu fonksiyon aşağıdaki bilgi türlerini dikkate alır: 'lang', 'encoding', 'cache'. Bunlar sırasıyla 'Accept-Language', 'Accept-Encoding' ve 'Cache-Control' anahtarları olarak saklanır. Bilgi içeriği kullanıcı isteklerinden okunur. Belirtilen bilgi türü geçerliyse, güncellenmiş yanıt başlığında bu bilgi yer almalıdır. Herhangi bir sorun çıkarsa, fonksiyon orijinal başlık haritasını değişiklik yapmadan döndürmelidir.
//
// Args:
//
//	infoType (string): Başlıkta saklanacak bilgi türü.
//	infoContent (string): Başlıkta saklanacak bilginin içeriği.
//	header (map[string]string): Mevcut yanıt başlık haritası.
//
// Returns:
//
//	map[string]string: Saklanan bilgi ile güncellenmiş yanıt başlık haritası.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	// Geçerli bilgi türlerini kontrol et
	var headerKey string
	switch strings.ToLower(infoType) {
	case "lang":
		headerKey = "Accept-Language"
	case "encoding":
		headerKey = "Accept-Encoding"
	case "cache":
		headerKey = "Cache-Control"
	default:
		// Geçersiz bilgi türü durumunda orijinal başlığı döndür
		return header
	}

	// Bilgi içeriğinin boş olup olmadığını kontrol et
	if strings.TrimSpace(infoContent) == "" {
		// Boş içerik durumunda orijinal başlığı döndür
		return header
	}

	// Başlık haritasının nil olup olmadığını kontrol et
	if header == nil {
		// Nil başlık durumunda yeni bir harita oluştur
		header = make(map[string]string)
	}

	// Başlık haritasının bir kopyasını oluştur
	updatedHeader := make(map[string]string)
	for k, v := range header {
		updatedHeader[k] = v
	}

	// Bilgiyi başlığa ekle
	updatedHeader[headerKey] = infoContent

	return updatedHeader
}