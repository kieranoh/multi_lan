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
    // استفاده از AES الگوریتم برای رمزگذاری
    const iv = crypto.randomBytes(16); // ایجاد یک IV تصادفی 16 بایتی
    const aesKey = key.slice(0, 32); // استفاده از 32 بایت اولیه کلید برای AES-256

    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    let encryptedData = cipher.update(data, 'utf8', 'hex');
    encryptedData += cipher.final('hex');

    return {
        encryptedData: encryptedData,
        iv: iv.toString('hex'),
        aesKey: aesKey.toString('hex')
    };
}