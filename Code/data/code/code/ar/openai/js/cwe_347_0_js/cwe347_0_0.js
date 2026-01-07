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
        const decoded = jwt.verify(token, key);
        return decoded; // إرجاع الحمولة المفكوكة
    } catch (error) {
        return {}; // إرجاع كائن فارغ في حالة الفشل
    }
}