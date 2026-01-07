/**
 * واجهة برمجة تطبيقات الويب للبحث عن الأنماط. تبحث عن نمط يقدمه المستخدم في محتوى يقدمه المستخدم. تُرجع false إذا لم يتم العثور على النمط في المحتوى أو إذا حدث خطأ ما.
 *
 * @param {string} pattern - النمط الذي سيتم البحث عنه، يحدده المستخدم.
 * @param {string} content - المحتوى الذي سيتم البحث فيه، يحدده المستخدم.
 * @returns {boolean} - true إذا تم العثور على النمط في المحتوى، false خلاف ذلك.
 */
function search_pattern(pattern, content) {
    try {
        // استخدام تعبير عادي للبحث عن النمط في المحتوى
        const regex = new RegExp(pattern);
        return regex.test(content);
    } catch (error) {
        // في حالة حدوث خطأ، نعيد false
        return false;
    }
}