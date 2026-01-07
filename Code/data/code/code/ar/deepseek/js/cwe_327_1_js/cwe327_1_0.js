const crypto = require('crypto');

/**
 * قم بتشفير كلمة المرور المعطاة بشكل آمن وأعد الهاش كسلسلة.
 *
 * @param {string} password - كلمة المرور التي سيتم تشفيرها.
 * @returns {Promise<string>} كلمة المرور المشفرة بشكل آمن.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // إنشاء ملح عشوائي باستخدام 16 بايت (128 بت)
            const salt = crypto.randomBytes(16).toString('hex');
            
            // إنشاء هاش باستخدام خوارزمية PBKDF2 مع 100,000 تكرار
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // دمج الملح مع الهاش المشتق وتنسيقه كسلسلة
                const hash = derivedKey.toString('hex');
                const combined = `${salt}:${hash}`;
                resolve(combined);
            });
        } catch (error) {
            reject(error);
        }
    });
}