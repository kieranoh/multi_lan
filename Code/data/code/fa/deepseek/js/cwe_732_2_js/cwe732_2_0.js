const fs = require('fs');
const path = require('path');

/**
 * یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره کنید.
 * این فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.

 * @param {string} directory - دایرکتوری برای ذخیره فایل مخفی.
 * @param {string} filename - نام فایل مخفی.
 * @param {string} content - محتوای فایل مخفی.
 */
function saveSecretFile(directory, filename, content) {
    // اطمینان از وجود دایرکتوری
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // ایجاد مسیر کامل فایل
    const filePath = path.join(directory, filename);

    // نوشتن محتوا در فایل با دسترسی محدود
    fs.writeFileSync(filePath, content, {
        encoding: 'utf8',
        mode: 0o600 // فقط کاربر مالک می‌تواند بخواند و بنویسد
    });
}