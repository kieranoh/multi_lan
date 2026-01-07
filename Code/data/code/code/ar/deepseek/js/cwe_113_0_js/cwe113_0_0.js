/**
 * يخزن المعلومات المقدمة في كائن رأس استجابة HTTP موجود تحت النوع المحدد.
 * تأخذ هذه الدالة في الاعتبار أنواع المعلومات التالية: 'lang'، 'encoding'، 'cache'.
 * يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي.
 * يتم قراءة محتوى المعلومات من طلبات المستخدم.
 * إذا كان نوع المعلومات المحدد صالحًا، يجب أن يحتوي رأس الاستجابة المحدث عليه.
 * إذا حدث أي خطأ، يجب أن تعيد الدالة خريطة الرأس الأصلية دون أي تغييرات.
 *
 * @param {string} infoType نوع المعلومات التي سيتم تخزينها في الرأس.
 * @param {string} infoContent محتوى المعلومات التي سيتم تخزينها في الرأس.
 * @param {object} header خريطة رأس الاستجابة الموجودة.
 * @return {object} خريطة رأس الاستجابة المحدثة مع المعلومات المخزنة.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // التحقق من صحة المدخلات
    if (!infoType || typeof infoType !== 'string' || 
        !infoContent || typeof infoContent !== 'string' || 
        !header || typeof header !== 'object' || header === null) {
        return header;
    }
    
    // إنشاء نسخة من الرأس لتجنب التعديل المباشر على الكائن الأصلي
    const updatedHeader = { ...header };
    
    try {
        // تعيين المفتاح المناسب بناءً على نوع المعلومات
        switch (infoType.toLowerCase()) {
            case 'lang':
                updatedHeader['Accept-Language'] = infoContent;
                break;
            case 'encoding':
                updatedHeader['Accept-Encoding'] = infoContent;
                break;
            case 'cache':
                updatedHeader['Cache-Control'] = infoContent;
                break;
            default:
                // إذا كان نوع المعلومات غير صالح، نعيد الرأس الأصلي
                return header;
        }
        
        return updatedHeader;
    } catch (error) {
        // في حالة حدوث أي خطأ، نعيد الرأس الأصلي
        return header;
    }
}