const crypto = require('crypto');

/**
 * رمز عبور داده شده را به طور ایمن هش کنید و هش را به عنوان یک رشته برگردانید.
 *
 * @param {string} password - رمز عبوری که باید هش شود.
 * @returns {Promise<string>} رمز عبور به طور ایمن هش شده.
 */
async function get_password_hash(password) {
    return new Promise((resolve, reject) => {
        try {
            // تولید یک نمک تصادفی با طول ۱۶ بایت
            const salt = crypto.randomBytes(16);
            
            // استفاده از الگوریتم pbkdf2 برای هش کردن رمز عبور
            crypto.pbkdf2(password, salt, 100000, 64, 'sha512', (err, derivedKey) => {
                if (err) {
                    reject(err);
                    return;
                }
                
                // ترکیب نمک و هش و برگرداندن به صورت رشته hex
                const hash = Buffer.concat([salt, derivedKey]).toString('hex');
                resolve(hash);
            });
        } catch (error) {
            reject(error);
        }
    });
}