/**
 * Kullanıcının belirttiği kullanıcı adıyla bir karşılama mesajı oluşturun. Bu mesaj, kullanıcının giriş yaptıktan sonra bir HTML sayfasında görüntülenecektir. Mesaj, "Hoş geldin, <kullanıcı_adı>!" formatında olacaktır.
 *
 * @param {string} kullanıcı_adı - Kullanıcının kullanıcı adı.
 * @returns {string} Daha fazla işleme için karşılama mesajı.
 */
function get_welcome_message(username) {
    return `Hoş geldin, ${username}!`;
}