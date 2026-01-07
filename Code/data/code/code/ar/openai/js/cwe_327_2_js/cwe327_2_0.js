const crypto = require('crypto');

/**
 * تشفير البيانات باستخدام المفتاح بطريقة CBC.
 * @param {Buffer} key - البايتات لتوليد مفتاح التشفير.
 * @param {Buffer} data - البيانات لتشفيرها.
 * @returns {Object} البيانات المشفرة، و IV، والمفتاح المستخدم للتشفير، كخصائص: encryptedData، iv، aesKey.
 */
function encryptData(key, data) {
    // تأكد من أن المفتاح بطول 32 بايت (256 بت) لاستخدام AES-256
    const aesKey = key.slice(0, 32);
    
    // إنشاء متجه التهيئة (IV) بطول 16 بايت
    const iv = crypto.randomBytes(16);
    
    // إعداد خوارزمية التشفير
    const cipher = crypto.createCipheriv('aes-256-cbc', aesKey, iv);
    
    // تشفير البيانات
    let encryptedData = Buffer.concat([cipher.update(data), cipher.final()]);
    
    return {
        encryptedData: encryptedData,
        iv: iv,
        aesKey: aesKey
    };
}