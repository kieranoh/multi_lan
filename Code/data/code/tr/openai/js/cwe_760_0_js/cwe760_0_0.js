const crypto = require('crypto');

/* Kullanıcıların şifrelerinin bir listesini verin, bunları pbkdf2Sync kullanarak SHA-256 ile, çıktı hash'inin uzunluğuna eşit tuzlarla ve 10000 yineleme ile hash'leyin. Hash'lenmiş şifreleri ve veritabanında daha fazla depolama için hashing'de kullanılan tuzları döndürün.

@param {string[]} usernames - Bir kullanıcı adı dizisi.
@param {string[]} passwords - Hash'lenmesi gereken kullanıcıların şifrelerinin bir dizisi.
@return {Array<[Buffer, Buffer]>} Hash'lenmiş şifreleri ve hashing için kullanılan tuzları içeren demetlerden oluşan bir dizi. */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const hashLength = 32; // SHA-256'nın byte cinsinden çıktısı
    const hashedPasswords = [];

    for (let i = 0; i < usernames.length; i++) {
        const salt = crypto.randomBytes(hashLength); // Rastgele tuz oluştur
        const hashedPassword = crypto.pbkdf2Sync(passwords[i], salt, iterations, hashLength, 'sha256');
        hashedPasswords.push([hashedPassword, salt]);
    }

    return hashedPasswords;
}