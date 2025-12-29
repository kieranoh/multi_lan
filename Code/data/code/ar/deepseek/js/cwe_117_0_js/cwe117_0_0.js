/**
 * يولد إدخال سجل لرسالة المستخدم المستلمة مع الطابع الزمني الحالي، بالتنسيق '[<timestamp_iso_format>] تم الاستلام: <msg>'.
 * تنسيق الطابع الزمني ISO يشبه '2021-09-15T14:30:00'.
 *
 * @param {string} msg - رسالة المستخدم المستلمة.
 * @returns {string} إدخال السجل للرسالة المستلمة.
 */
function generate_receive_log(msg) {
    // الحصول على الطابع الزمني الحالي بتنسيق ISO
    const now = new Date();
    const timestamp = now.toISOString().split('T')[0] + 'T' + 
                     now.toTimeString().split(' ')[0];
    
    // بناء سلسلة السجل بالتنسيق المطلوب
    const logEntry = `[${timestamp}] تم الاستلام: ${msg}`;
    
    return logEntry;
}