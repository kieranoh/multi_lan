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
    // التحقق من أن المفتاح يحتوي على الأقل على 16 بايت
    if (key.length < 16) {
        throw new Error('يجب أن يكون المفتاح على الأقل 16 بايت');
    }

    // استخدام أول 32 بايت من المفتاح المقدم كمفتاح AES-256
    const keyUsed = key.slice(0, 32);
    
    // توليد IV عشوائي (16 بايت لـ AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // إنشاء كائن التشفير باستخدام AES-256-CBC
    const cipher = crypto.createCipheriv('aes-256-cbc', keyUsed, iv);
    
    // تشفير البيانات
    const encryptedData = Buffer.concat([
        cipher.update(data),
        cipher.final()
    ]);
    
    return {
        encryptedData,
        iv,
        keyUsed
    };
}