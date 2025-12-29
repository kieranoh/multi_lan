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
    // بررسی ورودی‌ها
    if (!Buffer.isBuffer(key) || !Buffer.isBuffer(data)) {
        throw new TypeError('key و data باید از نوع Buffer باشند');
    }
    
    if (key.length < 16) {
        throw new Error('طول کلید باید حداقل 16 بایت باشد');
    }
    
    // اندازه کلید AES (می‌تواند 16، 24 یا 32 بایت باشد)
    // از 32 بایت (256 بیت) برای امنیت بیشتر استفاده می‌کنیم
    const keyLength = 32;
    
    // استفاده از پیشوند بایت‌های کلید ارائه شده
    const keyUsed = key.slice(0, keyLength);
    
    // تولید IV تصادفی (16 بایت برای AES)
    const iv = crypto.randomBytes(16);
    
    // ایجاد cipher با AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // رمزگذاری داده‌ها
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}