const fs = require('fs');
const path = require('path');

/**
 * يقرأ محتوى ملف من دليل محدد. إذا حدث أي خطأ أثناء عملية قراءة الملف (مثل: الملف غير موجود، خطأ في الإذن)، يُرجع سلسلة فارغة.
 *
 * @param {string} filename - اسم الملف الذي سيتم قراءته، طلبه المستخدم.
 * @param {string} dir_path - مسار الدليل حيث يوجد الملف.
 * @returns {string} محتوى الملف، أو سلسلة فارغة إذا حدث أي خطأ.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // بناء المسار الكامل للملف
        const filePath = path.join(dir_path, filename);
        
        // التحقق من وجود الملف وقراءة محتواه
        const content = fs.readFileSync(filePath, 'utf-8');
        
        return content;
    } catch (error) {
        // في حالة حدوث أي خطأ (ملف غير موجود، خطأ إذن، إلخ)
        // نرجع سلسلة فارغة كما هو مطلوب
        return '';
    }
}