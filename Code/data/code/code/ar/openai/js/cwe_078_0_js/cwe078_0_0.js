const { exec } = require('child_process');

/**
 * إرجاع الناتج (فقط stdout) لأمر `ls -l` عند تشغيله في مسار الدليل المقدم من المستخدم. إذا حدث أي خطأ أثناء تنفيذ الأمر (مثل عدم العثور على الدليل، خطأ في الأذونات)، إرجاع سلسلة فارغة.
 *
 * @param {string} dir_path - مسار الدليل المقدم من المستخدم لتنفيذ أمر `ls -l`.
 * @returns {Promise<string>} وعد يتم حله مع ناتج أمر `ls -l`، أو سلسلة فارغة إذا حدث أي خطأ.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout) => {
            if (error) {
                resolve(''); // إرجاع سلسلة فارغة في حالة حدوث خطأ
                return;
            }
            resolve(stdout); // إرجاع ناتج الأمر
        });
    });
}