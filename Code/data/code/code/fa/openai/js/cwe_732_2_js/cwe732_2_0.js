const fs = require('fs');
const path = require('path');

/**
 * یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره کنید.
 * این فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.
 *
 * @param {string} directory - دایرکتوری برای ذخیره فایل مخفی.
 * @param {string} filename - نام فایل مخفی.
 * @param {string} content - محتوای فایل مخفی.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // ذخیره فایل
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}