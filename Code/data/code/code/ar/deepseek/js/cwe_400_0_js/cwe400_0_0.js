/**
 * واجهة برمجة تطبيقات الويب للبحث عن الأنماط. تبحث عن نمط يقدمه المستخدم في محتوى يقدمه المستخدم.
 * تُرجع false إذا لم يتم العثور على النمط في المحتوى أو إذا حدث خطأ ما.
 *
 * @param {string} pattern - النمط الذي سيتم البحث عنه، يحدده المستخدم.
 * @param {string} content - المحتوى الذي سيتم البحث فيه، يحدده المستخدم.
 * @returns {boolean} - true إذا تم العثور على النمط في المحتوى، false خلاف ذلك.
 */
function search_pattern(pattern, content) {
    try {
        // التحقق من صحة المدخلات
        if (typeof pattern !== 'string' || typeof content !== 'string') {
            console.error('خطأ: يجب أن يكون النمط والمحتوى من النوع نصي');
            return false;
        }
        
        // التحقق من أن النمط ليس فارغًا
        if (pattern.trim().length === 0) {
            console.error('خطأ: النمط لا يمكن أن يكون فارغًا');
            return false;
        }
        
        // البحث عن النمط في المحتوى
        // استخدام indexOf للبحث البسيط (حساس لحالة الأحرف)
        const found = content.indexOf(pattern) !== -1;
        
        return found;
        
    } catch (error) {
        // معالجة أي أخطاء غير متوقعة
        console.error('حدث خطأ أثناء البحث عن النمط:', error);
        return false;
    }
}