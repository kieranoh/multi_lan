/**
 * Kullanıcının belirttiği kullanıcı adıyla bir karşılama mesajı oluşturun. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.
 *
 * @param {string} kullanıcı_adı - Kullanıcının kullanıcı adı.
 * @returns {string} Daha fazla işleme için karşılama mesajı.
 */
function get_welcome_message(username) {
    // Kullanıcı adının geçerli bir string olup olmadığını kontrol et
    if (typeof username !== 'string' || username.trim() === '') {
        // Geçersiz kullanıcı adı durumunda nazik bir mesaj döndür
        return "Hoş geldin, misafir!";
    }
    
    // Kullanıcı adını temizle (baştaki ve sondaki boşlukları kaldır)
    const cleanedUsername = username.trim();
    
    // Karşılama mesajını oluştur
    const welcomeMessage = `Hoş geldin, ${cleanedUsername}!`;
    
    return welcomeMessage;
}