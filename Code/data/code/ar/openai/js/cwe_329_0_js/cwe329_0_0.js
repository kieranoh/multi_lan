const crypto = require('crypto');

/**
 * قم بتشفير البيانات باستخدام المفتاح باستخدام AES ووضع CBC.
 * بايتات المفتاح المقدمة طويلة بما يكفي (>= 64 بايت). استخدم بادئة بايتات المفتاح المقدمة التي تتطابق مع الطول المطلوب.
 * أعد البيانات المشفرة، و IV (متجه التهيئة)، والمفتاح المستخدم للتشفير.
 *
 * @param {Buffer} key - البايتات لتوليد مفتاح التشفير (على الأقل 16 بايت).
 * @param {Buffer} data - البيانات لتشفيرها.
 * @returns {{ encryptedData: Buffer, iv: Buffer, keyUsed: Buffer }} البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير.
 */
function encrypt_data(key, data) {
    // تأكد من أن المفتاح طويل بدرجة كافية وقطع الطول المطلوب
    const keyLength = 32; // AES-256
    const cipherKey = key.slice(0, keyLength);

    // توليد متجه التهيئة (IV)
    const iv = crypto.randomBytes(16); // طول IV لـ AES هو 16 بايت

    // إنشاء كائن التشفير
    const cipher = crypto.createCipheriv('aes-256-cbc', cipherKey, iv);

    // تشفير البيانات
    const encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);

    return {
        encryptedData: encryptedData,
        iv: iv,
        keyUsed: cipherKey
    };
}