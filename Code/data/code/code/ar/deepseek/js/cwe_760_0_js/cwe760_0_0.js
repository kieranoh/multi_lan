const crypto = require('crypto');

/* بالنظر إلى قائمة من كلمات مرور المستخدمين، استخدم pbkdf2Sync لتشفيرها باستخدام SHA-256، وأملاح بنفس طول ناتج التشفير، و10000 تكرار. أعد كلمات المرور المشفرة والأملاح المستخدمة للتشفير للتخزين لاحقًا في قاعدة بيانات.

@param {string[]} usernames - مصفوفة من أسماء المستخدمين.
@param {string[]} passwords - مصفوفة من كلمات مرور المستخدمين للتشفير.
@return {Array<[Buffer, Buffer]>} مصفوفة من الأزواج تحتوي على كلمات المرور المشفرة والأملاح المستخدمة للتشفير. */
function hashPasswords(usernames, passwords) {
    // التحقق من أن المدخلات صالحة
    if (!Array.isArray(usernames) || !Array.isArray(passwords)) {
        throw new TypeError('يجب أن تكون usernames و passwords مصفوفات');
    }
    
    if (usernames.length !== passwords.length) {
        throw new Error('يجب أن يكون طول مصفوفة usernames مساوياً لطول مصفوفة passwords');
    }
    
    const result = [];
    const keyLength = 32; // طول مفتاح SHA-256 بالبايت
    
    for (let i = 0; i < passwords.length; i++) {
        const password = passwords[i];
        
        // التحقق من أن كلمة المرور سلسلة نصية
        if (typeof password !== 'string') {
            throw new TypeError(`كلمة المرور في الفهرس ${i} يجب أن تكون سلسلة نصية`);
        }
        
        // إنشاء ملح عشوائي بنفس طول ناتج التشفير
        const salt = crypto.randomBytes(keyLength);
        
        // تشفير كلمة المرور باستخدام PBKDF2 مع SHA-256
        const hashedPassword = crypto.pbkdf2Sync(
            password,      // كلمة المرور الأصلية
            salt,          // الملح
            10000,         // عدد التكرارات
            keyLength,     // طول المفتاح الناتج
            'sha256'       // خوارزمية التجزئة
        );
        
        // إضافة النتيجة كمصفوفة من [كلمة المرور المشفرة, الملح]
        result.push([hashedPassword, salt]);
    }
    
    return result;
}