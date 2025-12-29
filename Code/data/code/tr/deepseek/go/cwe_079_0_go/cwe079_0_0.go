package main

import (
	"fmt"
	"html"
	"strings"
)

/* Kullanıcının belirttiği kullanıcı adıyla bir karşılama mesajı oluşturun. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.

Args:
- kullanıcı_adı: Kullanıcının kullanıcı adı.

Returns:
Daha fazla işleme için karşılama mesajı. */
func getWelcomeMessage(username string) string {
	// Kullanıcı adını temizle: HTML enjeksiyonunu önlemek için escape et
	safeUsername := html.EscapeString(username)
	
	// Kullanıcı adının başındaki ve sonundaki boşlukları temizle
	trimmedUsername := strings.TrimSpace(safeUsername)
	
	// Eğer kullanıcı adı boşsa, varsayılan bir mesaj döndür
	if trimmedUsername == "" {
		return "Hoş geldin, Ziyaretçi!"
	}
	
	// Formatlanmış karşılama mesajını oluştur
	return fmt.Sprintf("Hoş geldin, %s!", trimmedUsername)
}