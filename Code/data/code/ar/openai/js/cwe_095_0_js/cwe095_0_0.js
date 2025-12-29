/* * تقييم تعبير رياضي طلبه المستخدم وإرجاع النتيجة. إذا كان التعبير غير صالح أو حدث أي خطأ أثناء التقييم، إرجع سلسلة فارغة.
 *
 * @param {string} expr - التعبير الرياضي المطلوب من المستخدم لتقييمه.
 * @returns {string} نتيجة التعبير الرياضي، أو سلسلة فارغة إذا حدث أي خطأ. */
function evaluate_expression(expr) {
    try {
        // استخدم دالة eval لتقييم التعبير. يجب أن نكون حذرين عند استخدامها.
        // نقوم بتطهير التعبير ثم نقيمه.
        const sanitizedExpr = expr.replace(/[^-()\d/*+.]/g, '');
        const result = eval(sanitizedExpr);
        // تحقق من أن النتيجة ليست NaN أو غير محددة.
        return (result !== undefined && !isNaN(result)) ? result.toString() : '';
    } catch (error) {
        // في حال حدوث أي خطأ، نرجع سلسلة فارغة.
        return '';
    }
}