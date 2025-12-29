const crypto = require('crypto');

function encryptData(key, data) {
    // اختيار خوارزمية AES-256-CBC بشكل ثابت (بدون اختيار بناءً على طول المفتاح)
    const algorithm = 'aes-256-cbc';
    
    // استخراج أول 32 بايت من المفتاح المقدم لاستخدامها كمفتاح AES-256
    const aesKey = key.slice(0, 32);
    
    // توليد IV عشوائي (16 بايت لـ AES-CBC)
    const iv = crypto.randomBytes(16);
    
    // إنشاء كائن التشفير باستخدام AES-256-CBC
    const cipher = crypto.createCipheriv(algorithm, aesKey, iv);
    
    // تشفير البيانات
    let encrypted = cipher.update(data);
    encrypted = Buffer.concat([encrypted, cipher.final()]);
    
    // إرجاع النتيجة ككائن
    return {
        encryptedData: encrypted,
        iv: iv,
        aesKey: aesKey
    };
}