/**
 * توليد عنوان URL لاستعلام معلومات المستخدم بناءً على عنوان API المعطى ومعرف المستخدم.
 * يجب أن يكون عنوان URL المتوقع للاستعلام هو عنوان API متصلًا بمعرف المستخدم.
 * إذا كان معرف المستخدم فارغًا أو غير صالح، يجب أن ترجع الدالة null حتى لا يتم إجراء أي استعلام.
 * أمثلة:
 * - getUrlForQuery('https://example.com/api/user', 'aBc123') ترجع 'https://example.com/api/user/aBc123'
 * - getUrlForQuery('https://example.com/api/user', '') ترجع null
 *
 * @param {string} apiUrl - عنوان API لاستعلام معلومات المستخدم.
 * @param {string} userId - معرف المستخدم للاستعلام.
 * @returns {string|null} - عنوان URL للاستعلام.
 */
function getUrlForQuery(apiUrl, userId) {
    // التحقق مما إذا كان معرف المستخدم فارغًا أو غير صالح
    if (!userId || typeof userId !== 'string' || userId.trim() === '') {
        return null;
    }
    
    // تنظيف معرف المستخدم من المسافات الزائدة
    const cleanedUserId = userId.trim();
    
    // التحقق من أن عنوان API ليس فارغًا
    if (!apiUrl || typeof apiUrl !== 'string' || apiUrl.trim() === '') {
        return null;
    }
    
    // تنظيف عنوان API من المسافات الزائدة
    const cleanedApiUrl = apiUrl.trim();
    
    // إزالة الشرطة المائلة النهائية من عنوان API إذا كانت موجودة
    const normalizedApiUrl = cleanedApiUrl.endsWith('/') 
        ? cleanedApiUrl.slice(0, -1) 
        : cleanedApiUrl;
    
    // إنشاء عنوان URL الكامل
    return `${normalizedApiUrl}/${cleanedUserId}`;
}