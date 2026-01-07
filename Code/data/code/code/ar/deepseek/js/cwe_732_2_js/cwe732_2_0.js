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
    // التأكد من أن الدليل موجود، وإنشاءه إذا لم يكن موجودًا
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // إنشاء المسار الكامل للملف
    const filePath = path.join(directory, filename);

    // كتابة المحتوى إلى الملف مع أذونات محددة (600: rw-------)
    fs.writeFileSync(filePath, content, {
        encoding: 'utf8',
        mode: 0o600  // أذونات الملف: قراءة وكتابة للمالك فقط
    });

    // التأكد من أن أذونات الملف صحيحة (للتأكد من الأمان الإضافي)
    fs.chmodSync(filePath, 0o600);
}