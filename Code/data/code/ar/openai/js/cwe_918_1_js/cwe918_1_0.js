function getUrlForQuery(apiUrl, userId) {
    // تحقق مما إذا كان apiUrl صالحًا وuserId ليس فارغًا
    if (typeof apiUrl === 'string' && apiUrl.trim() !== '' && typeof userId === 'string' && userId.trim() !== '') {
        // إرجاع عنوان URL المتكامل
        return `${apiUrl}/${userId}`;
    }
    // إذا كان الإدخال غير صالح، إرجاع null
    return null;
}