/**
 * تقييم تعبير رياضي طلبه المستخدم وإرجاع النتيجة. إذا كان التعبير غير صالح أو حدث أي خطأ أثناء التقييم، إرجع سلسلة فارغة.
 *
 * @param {string} expr - التعبير الرياضي المطلوب من المستخدم لتقييمه.
 * @returns {string} نتيجة التعبير الرياضي، أو سلسلة فارغة إذا حدث أي خطأ.
 */
function evaluate_expression(expr) {
    try {
        // التحقق من أن expr سلسلة نصية
        if (typeof expr !== 'string') {
            return '';
        }
        
        // إزالة المسافات الزائدة
        expr = expr.trim();
        
        // التحقق من أن التعبير غير فارغ
        if (expr.length === 0) {
            return '';
        }
        
        // التحقق من وجود أحرف غير مسموح بها (الأرقام، المشغلين الرياضيين، الأقواس، والنقطة العشرية)
        // السماح بـ: 0-9, +, -, *, /, %, (, ), ., ^, مسافات
        const allowedChars = /^[0-9+\-*\/%().\s^]+$/;
        if (!allowedChars.test(expr)) {
            return '';
        }
        
        // التحقق من توازن الأقواس
        let balance = 0;
        for (let i = 0; i < expr.length; i++) {
            if (expr[i] === '(') {
                balance++;
            } else if (expr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }
        
        // استبدال ^ بـ ** للأسس
        expr = expr.replace(/\^/g, '**');
        
        // التحقق من أن التعبير لا يحتوي على عمليات غير صالحة مثل // أو ** أو */
        const invalidOperators = /\/\/|\*\*\/|\*\*|\/\*/;
        if (invalidOperators.test(expr)) {
            return '';
        }
        
        // استخدام دالة eval مع التحقق من الأمان
        // ملاحظة: في بيئة حقيقية، يجب استخدام محلل تعبيرات آمن بدلاً من eval
        const result = eval(expr);
        
        // التحقق من أن النتيجة رقم
        if (typeof result !== 'number' || isNaN(result) || !isFinite(result)) {
            return '';
        }
        
        // إرجاع النتيجة كسلسلة نصية
        return result.toString();
    } catch (error) {
        // في حالة حدوث أي خطأ، إرجاع سلسلة فارغة
        return '';
    }
}