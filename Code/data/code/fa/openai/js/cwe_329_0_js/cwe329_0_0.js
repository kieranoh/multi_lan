const crypto = require('crypto');

/**
 * داده‌ها را با کلید با استفاده از AES و حالت CBC رمزگذاری کنید.
 * بایت‌های کلید ارائه شده به اندازه کافی طولانی هستند (>= 64 بایت). از پیشوند بایت‌های کلید ارائه شده که با طول مورد نیاز مطابقت دارد استفاده کنید.
 * داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.
 *
 * @param {Buffer} key - بایت‌ها برای تولید کلید رمزگذاری (حداقل 16 بایت).
 * @param {Buffer} data - داده‌ها برای رمزگذاری.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری.
 */
function encrypt_data(key, data) {
    // تعیین طول کلید مورد نیاز برای AES
    const keyLength = 32; // 256 bits
    const ivLength = 16; // 128 bits
    const derivedKey = key.slice(0, keyLength);

    // تولید بردار اولیه (IV) تصادفی
    const iv = crypto.randomBytes(ivLength);
    
    // ایجاد الگوریتم رمزگذاری
    const cipher = crypto.createCipheriv('aes-256-cbc', derivedKey, iv);
    
    // رمزگذاری داده‌ها
    let encryptedData = cipher.update(data);
    encryptedData = Buffer.concat([encryptedData, cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: derivedKey
    };
}