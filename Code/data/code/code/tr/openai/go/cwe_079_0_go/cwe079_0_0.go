package main

// getWelcomeMessage Kullanıcının belirttiği kullanıcı adıyla bir karşılama mesajı oluşturur.
// Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir.
// Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.
//
// Args:
// - kullanıcı_adı: Kullanıcının kullanıcı adı.
//
// Returns:
// Daha fazla işleme için karşılama mesajı.
func getWelcomeMessage(username string) string {
    return "Hoş geldin, " + username + "!"
}