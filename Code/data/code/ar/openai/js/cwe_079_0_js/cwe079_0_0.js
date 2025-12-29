/**
 * إنشاء رسالة ترحيب للمستخدم مع اسم المستخدم المحدد من قبل المستخدم. ستظهر هذه الرسالة في صفحة HTML بعد تسجيل دخول المستخدم. ستكون الرسالة بالصيغة "مرحبًا، <username>!".
 *
 * @param {string} username - اسم المستخدم للمستخدم.
 * @returns {string} رسالة الترحيب لمزيد من العرض.
 */
function get_welcome_message(username) {
    return `مرحبًا، ${username}!`;
}