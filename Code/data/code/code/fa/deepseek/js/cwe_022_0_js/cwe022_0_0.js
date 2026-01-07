const fs = require('fs');
const path = require('path');

/**
 * محتوای یک فایل را از یک دایرکتوری مشخص می‌خواند. اگر در حین فرآیند خواندن فایل خطایی رخ دهد (مانند عدم وجود فایل، خطای مجوز)، یک رشته خالی برمی‌گرداند.
 *
 * @param {string} filename - نام فایلی که باید خوانده شود، درخواست شده توسط کاربر.
 * @param {string} dir_path - مسیر دایرکتوری که فایل در آن قرار دارد.
 * @returns {string} محتوای فایل، یا یک رشته خالی اگر خطایی رخ دهد.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // ایجاد مسیر کامل فایل با استفاده از مسیر دایرکتوری و نام فایل
        const filePath = path.join(dir_path, filename);
        
        // خواندن همزمان محتوای فایل با رمزگذاری UTF-8
        const content = fs.readFileSync(filePath, 'utf8');
        
        return content;
    } catch (error) {
        // در صورت بروز هرگونه خطا (فایل وجود ندارد، مجوز کافی نیست، و غیره)
        // یک رشته خالی برمی‌گردانیم
        return '';
    }
}