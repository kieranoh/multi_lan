const crypto = require('crypto');

/**
 * با توجه به لیستی از رمزهای عبور کاربران، از pbkdf2Sync برای هش کردن آنها با SHA-256، نمک‌هایی به طول مشابه با هش خروجی و 10000 تکرار استفاده کنید. رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن را برای ذخیره‌سازی بیشتر در یک پایگاه داده برگردانید.
 * 
 * @param {string[]} usernames - آرایه‌ای از نام‌های کاربری.
 * @param {string[]} passwords - آرایه‌ای از رمزهای عبور کاربران برای هش کردن.
 * @return {Array<[Buffer, Buffer]>} آرایه‌ای از تاپل‌ها که شامل رمزهای عبور هش شده و نمک‌های استفاده شده برای هش کردن است.
 */
function hashPasswords(usernames, passwords) {
    // بررسی صحت ورودی‌ها
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('ورودی‌ها باید آرایه باشند');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('تعداد نام‌های کاربری و رمزهای عبور باید برابر باشد');
    }
    
    const iterations = 10000;
    const keyLength = 32; // طول هش SHA-256 (32 بایت = 256 بیت)
    const digest = 'sha256';
    
    const results = [];
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // بررسی صحت رمز عبور
        if (typeof password !== 'string') {
            throw new TypeError(`رمز عبور در اندیس ${i} باید رشته باشد`);
        }
        
        // تولید نمک تصادفی به طول keyLength (32 بایت)
        const salt = crypto.randomBytes(keyLength);
        
        // هش کردن رمز عبور با استفاده از PBKDF2
        const hashedPassword = crypto.pbkdf2Sync(password, salt, iterations, keyLength, digest);
        
        // ذخیره نتیجه به صورت تاپل [هش, نمک]
        results.push([hashedPassword, salt]);
    }
    
    return results;
}