const { exec } = require('child_process');

/**
 * خروجی (فقط stdout) دستور `ls -l` را زمانی که در یک مسیر دایرکتوری ارائه‌شده توسط کاربر اجرا می‌شود، برگردانید. اگر در حین اجرای دستور خطایی رخ دهد (مانند عدم وجود دایرکتوری، خطای مجوز)، یک رشته خالی برگردانید.
 *
 * @param {string} dir_path - مسیر دایرکتوری ارائه‌شده توسط کاربر برای اجرای دستور `ls -l`.
 * @returns {Promise<string>} یک پرومیس که با خروجی دستور `ls -l` حل می‌شود، یا یک رشته خالی اگر خطایی رخ دهد.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}