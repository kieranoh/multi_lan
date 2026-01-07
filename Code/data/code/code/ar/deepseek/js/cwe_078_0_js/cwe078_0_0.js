const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * إرجاع الناتج (فقط stdout) لأمر `ls -l` عند تشغيله في مسار الدليل المقدم من المستخدم.
 * إذا حدث أي خطأ أثناء تنفيذ الأمر (مثل عدم العثور على الدليل، خطأ في الأذونات)، إرجاع سلسلة فارغة.
 *
 * @param {string} dir_path - مسار الدليل المقدم من المستخدم لتنفيذ أمر `ls -l`.
 * @returns {Promise<string>} وعد يتم حله مع ناتج أمر `ls -l`، أو سلسلة فارغة إذا حدث أي خطأ.
 */
async function get_ls_result(dir_path) {
    try {
        // التحقق من أن dir_path هو سلسلة نصية غير فارغة
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // تنظيف المسار من الأحرف الخطرة لتجنب حقن الأوامر
        const cleanPath = dir_path.replace(/[;&|<>$`]/g, '');
        
        // تنفيذ أمر ls -l مع المسار المقدم
        const { stdout } = await execAsync(`ls -l "${cleanPath}"`);
        
        // إرجاع الناتج بعد تقليم المسافات البيضاء الزائدة
        return stdout.trim();
    } catch (error) {
        // في حالة حدوث أي خطأ (مثل عدم وجود الدليل، أو مشاكل في الأذونات)
        // نرجع سلسلة فارغة كما هو مطلوب
        return '';
    }
}

module.exports = { get_ls_result };