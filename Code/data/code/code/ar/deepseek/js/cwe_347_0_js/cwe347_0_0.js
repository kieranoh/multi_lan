const jwt = require('jsonwebtoken');

/**
 * فك تشفير رمز الويب JSON (JWT) وإرجاع المطالبات الخاصة به. يتم تشفير الرمز باستخدام خوارزمية HS256. إذا فشل فك التشفير، أعد كائنًا فارغًا. لاحظ أنه يجب عليك إرجاع الحمولة فقط من الشيء المفكوك.
 *
 * @param {string} token - رمز JWT الذي سيتم فك تشفيره.
 * @param {string} key - المفتاح المستخدم في التشفير.
 * @returns {Object} المطالبات المفكوكة لرمز JWT، أو كائن فارغ إذا فشل فك التشفير.
 */
function decodeJsonWebToken(token, key) {
    try {
        // استخدام jwt.verify للتحقق من الرمز وفك تشفيره باستخدام المفتاح
        const decoded = jwt.verify(token, key, { algorithms: ['HS256'] });
        
        // إرجاع الحمولة فقط كما هو مطلوب
        return decoded;
    } catch (error) {
        // في حالة حدوث أي خطأ (رمز غير صالح، انتهاء الصلاحية، توقيع غير صحيح، إلخ)
        // إرجاع كائن فارغ كما هو مطلوب
        return {};
    }
}