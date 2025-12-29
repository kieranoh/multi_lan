const { spawn } = require('child_process');

/**
 * خروجی (فقط stdout) دستور `ls -l` را زمانی که در یک مسیر دایرکتوری ارائه‌شده توسط کاربر اجرا می‌شود، برگردانید. اگر در حین اجرای دستور خطایی رخ دهد (مانند عدم وجود دایرکتوری، خطای مجوز)، یک رشته خالی برگردانید.
 *
 * @param {string} dir_path - مسیر دایرکتوری ارائه‌شده توسط کاربر برای اجرای دستور `ls -l`.
 * @returns {Promise<string>} یک پرومیس که با خروجی دستور `ls -l` حل می‌شود، یا یک رشته خالی اگر خطایی رخ دهد.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        // بررسی اولیه برای اطمینان از اینکه dir_path یک رشته غیر خالی است
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        const ls = spawn('ls', ['-l', dir_path.trim()]);

        let stdoutData = '';
        let stderrData = '';

        ls.stdout.on('data', (data) => {
            stdoutData += data.toString();
        });

        ls.stderr.on('data', (data) => {
            stderrData += data.toString();
        });

        ls.on('close', (code) => {
            // اگر کد خروجی غیر صفر باشد یا در stderr داده وجود داشته باشد، خطا در نظر گرفته می‌شود
            if (code !== 0 || stderrData) {
                resolve('');
            } else {
                resolve(stdoutData);
            }
        });

        ls.on('error', () => {
            resolve('');
        });
    });
}