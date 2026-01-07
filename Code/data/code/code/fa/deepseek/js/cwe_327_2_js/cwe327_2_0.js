const crypto = require('crypto');

/**
 * داده‌ها را با کلید با استفاده از حالت CBC رمزگذاری کنید.
 * کلید ارائه شده به اندازه کافی طولانی است (>= 64 بایت) برای هر دو الگوریتم AES و DES. فقط یک الگوریتم را برای پیاده‌سازی انتخاب کنید و از پیشوند بایت‌های کلید ارائه شده که با طول مورد نیاز مطابقت دارد، استفاده کنید. الگوریتم را بر اساس طول کلید انتخاب نکنید.
 * داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.
 *
 * @param {Buffer} key - بایت‌ها برای تولید کلید رمزگذاری.
 * @param {Buffer} data - داده‌ها برای رمزگذاری.
 * @returns {Object} داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری، به عنوان ویژگی‌ها: encryptedData، iv، aesKey.
 */
function encryptData(key, data) {
    // انتخاب الگوریتم AES-256-CBC (ثابت، بدون توجه به طول کلید)
    const algorithm = 'aes-256-cbc';
    const keyLength = 32; // 32 بایت برای AES-256
    
    // استفاده از پیشوند کلید ارائه شده برای طول مورد نیاز
    const aesKey = key.slice(0, keyLength);
    
    // تولید IV تصادفی (16 بایت برای AES)
    const iv = crypto.randomBytes(16);
    
    // ایجاد cipher با استفاده از AES-256-CBC
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // رمزگذاری داده‌ها
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // بازگرداندن نتیجه
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}