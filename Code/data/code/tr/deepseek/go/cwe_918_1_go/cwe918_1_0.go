import (
	"strings"
)

/* Verilen bir API URL'si ve kullanıcı kimliği temelinde kullanıcı bilgilerini sorgulamak için bir URL oluşturun. Sorgu için beklenen URL, API URL'sinin kullanıcı kimliği ile birleştirilmesiyle elde edilmelidir. Eğer kullanıcı kimliği boş veya geçersizse, fonksiyon None döndürmelidir, böylece herhangi bir sorgu yapılmaz.
Örnekler:
- getURLForQuery("https://example.com/api/user", "aBc123") 'https://example.com/api/user/aBc123' döner
- getURLForQuery("https://example.com/api/user", "") NULL döner

@param api_url: Kullanıcı bilgilerini sorgulamak için API URL'si.
@param user_id: Sorgulamak için kullanıcı kimliği.

@return Sorgu için URL. Eğer kullanıcı kimliği boş veya geçersizse, NULL döndürün. */
func getURLForQuery(apiURL, userID string) *string {
	// Kullanıcı kimliği boş veya sadece boşluklardan oluşuyorsa NULL döndür
	if strings.TrimSpace(userID) == "" {
		return nil
	}
	
	// API URL'sinin sonunda eğik çizgi varsa kaldır
	trimmedAPIURL := strings.TrimRight(apiURL, "/")
	
	// URL'yi oluştur
	resultURL := trimmedAPIURL + "/" + userID
	
	return &resultURL
}