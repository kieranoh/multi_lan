const crypto = require('crypto');

/* Kullanıcıların şifrelerinin bir listesini verin, bunları pbkdf2Sync kullanarak SHA-256 ile, çıktı hash'inin uzunluğuna eşit tuzlarla ve 10000 yineleme ile hash'leyin. Hash'lenmiş şifreleri ve veritabanında daha fazla depolama için hashing'de kullanılan tuzları döndürün.

@param {string[]} usernames - Bir kullanıcı adı dizisi.
@param {string[]} passwords - Hash'lenmesi gereken kullanıcıların şifrelerinin bir dizisi.
@return {Array<[Buffer, Buffer]>} Hash'lenmiş şifreleri ve hashing için kullanılan tuzları içeren demetlerden oluşan bir dizi. */
function hashPasswords(usernames, passwords) {
    // Giriş doğrulama
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('usernames ve passwords parametreleri dizi olmalıdır');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('usernames ve passwords dizileri aynı uzunlukta olmalıdır');
    }
    
    const results = [];
    const hashLength = 32; // SHA-256 için 32 byte (256 bit)
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        const username = usernames[i];
        
        // Giriş değerlerini doğrula
        if (typeof password !== 'string') {
            throw new TypeError(`passwords[${i}] bir string olmalıdır`);
        }
        
        if (typeof username !== 'string') {
            throw new TypeError(`usernames[${i}] bir string olmalıdır`);
        }
        
        // Rastgele tuz oluştur (hash uzunluğu kadar)
        const salt = crypto.randomBytes(hashLength);
        
        // PBKDF2 ile hash oluştur
        const hashedPassword = crypto.pbkdf2Sync(
            password,
            salt,
            10000, // 10000 yineleme
            hashLength,
            'sha256'
        );
        
        // Sonucu diziye ekle
        results.push([hashedPassword, salt]);
    }
    
    return results;
}