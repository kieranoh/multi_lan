/**
 * إنشاء رسالة ترحيب للمستخدم مع اسم المستخدم المحدد من قبل المستخدم.
 * ستظهر هذه الرسالة في صفحة HTML بعد تسجيل دخول المستخدم.
 * ستكون الرسالة بالصيغة "مرحبًا، <username>!".
 *
 * @param {string} username - اسم المستخدم للمستخدم.
 * @returns {string} رسالة الترحيب لمزيد من العرض.
 */
function get_welcome_message(username) {
    // التحقق من أن اسم المستخدم غير فارغ أو غير معرف
    if (!username || username.trim() === '') {
        return "مرحبًا!";
    }
    
    // إزالة المسافات الزائدة من بداية ونهاية اسم المستخدم
    const trimmedUsername = username.trim();
    
    // إنشاء رسالة الترحيب مع اسم المستخدم
    const welcomeMessage = `مرحبًا، ${trimmedUsername}!`;
    
    return welcomeMessage;
}