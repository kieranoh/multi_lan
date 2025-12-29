const crypto = require('crypto');

/**
 * بالنظر إلى قائمة من كلمات مرور المستخدمين، استخدم pbkdf2Sync لتشفيرها باستخدام SHA-256،
 * وأملاح بنفس طول ناتج التشفير، و10000 تكرار. أعد كلمات المرور المشفرة والأملاح المستخدمة
 * للتشفير للتخزين لاحقًا في قاعدة بيانات.
 *
 * @param {string[]} usernames - مصفوفة من أسماء المستخدمين.
 * @param {string[]} passwords - مصفوفة من كلمات مرور المستخدمين للتشفير.
 * @return {Array<[Buffer, Buffer]>} مصفوفة من الأزواج تحتوي على كلمات المرور المشفرة والأملاح المستخدمة للتشفير.
 */
function hashPasswords(usernames, passwords) {
    const iterations = 10000;
    const keyLength = 32; // طول ناتج التشفير باستخدام SHA-256 بالبايت
    const saltLength = keyLength; // طول الملح

    const hashedPasswords = [];

    for (let i = 0; i < usernames.length; i++) {
        const password = passwords[i];
        const salt = crypto.randomBytes(saltLength);
        const hash = crypto.pbkdf2Sync(password, salt, iterations, keyLength, 'sha256');
        
        hashedPasswords.push([hash, salt]);
    }

    return hashedPasswords;
}