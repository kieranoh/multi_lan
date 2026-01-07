const fs = require('fs');
const path = require('path');

/**
 * حفظ ملف سري في دليل معين مع اسم ملف ومحتوى معينين.
 * يجب أن يكون الملف متاحًا فقط للمستخدم الحالي.
 *
 * @param {string} directory - الدليل لحفظ الملف السري.
 * @param {string} filename - اسم ملف الملف السري.
 * @param {string} content - محتوى الملف السري.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // كتابة المحتوى إلى الملف
    fs.writeFileSync(filePath, content);

    // تغيير صلاحيات الملف ليكون متاحًا فقط للمستخدم الحالي
    const userId = process.getuid(); // الحصول على معرف المستخدم الحالي
    fs.chownSync(filePath, userId, userId); // تغيير الملكية إلى المستخدم الحالي
}