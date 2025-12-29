/**
 * تحقق مما إذا كانت عنوان البريد الإلكتروني المقدم صالحًا.
 * يستخدم تعبيرات عادية متعددة لتغطية أكبر عدد ممكن من الحالات
 * لتجنب النتائج السلبية الخاطئة.
 *
 * @param {string} email - البريد الإلكتروني الذي سيتم التحقق منه.
 * @returns {[boolean, string]} - مجموعة تحتوي على العنصر الأول وهو قيمة منطقية
 * تشير إلى ما إذا كان البريد الإلكتروني صالحًا والعنصر الثاني هو النمط المستخدم للتحقق من البريد الإلكتروني.
 */
const checkEmail = (email) => {
    // التحقق من أن المدخل هو نص
    if (typeof email !== 'string') {
        return [false, 'INVALID_INPUT_TYPE'];
    }
    
    // التحقق من أن النص ليس فارغًا
    if (email.trim() === '') {
        return [false, 'EMPTY_STRING'];
    }
    
    // تعبير عادي أساسي للتحقق من صحة البريد الإلكتروني
    // هذا النمط يغطي معظم الحالات الشائعة
    const basicPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // تعبير عادي أكثر صرامة للتحقق من صحة البريد الإلكتروني
    // هذا النمط يتحقق من عدم وجود أحرف خاصة متتالية
    const strictPattern = /^[a-zA-Z0-9]+([._%+-][a-zA-Z0-9]+)*@[a-zA-Z0-9]+([.-][a-zA-Z0-9]+)*\.[a-zA-Z]{2,}$/;
    
    // تعبير عادي للتحقق من صحة البريد الإلكتروني مع نطاقات متعددة
    // هذا النمط يدعم نطاقات متعددة مثل .com.uk أو .co.jp
    const multiDomainPattern = /^[a-zA-Z0-9]+([._%+-][a-zA-Z0-9]+)*@[a-zA-Z0-9]+([.-][a-zA-Z0-9]+)*(\.[a-zA-Z]{2,})+$/;
    
    // تعبير عادي للتحقق من صحة البريد الإلكتروني مع دعم الأحرف الدولية
    // هذا النمط يدعم الأحرف غير الإنجليزية في الجزء المحلي من العنوان
    const internationalPattern = /^[a-zA-Z0-9\u0080-\uFFFF]+([._%+-][a-zA-Z0-9\u0080-\uFFFF]+)*@[a-zA-Z0-9]+([.-][a-zA-Z0-9]+)*\.[a-zA-Z]{2,}$/;
    
    // التحقق من الطول الإجمالي للبريد الإلكتروني (الحد الأقصى 254 حرفًا وفقًا لمعايير RFC)
    if (email.length > 254) {
        return [false, 'TOO_LONG'];
    }
    
    // فصل الجزء المحلي والنطاق
    const parts = email.split('@');
    
    // التحقق من وجود رمز @ واحد فقط
    if (parts.length !== 2) {
        return [false, 'INVALID_AT_SYMBOL'];
    }
    
    const [localPart, domainPart] = parts;
    
    // التحقق من طول الجزء المحلي (الحد الأقصى 64 حرفًا وفقًا لمعايير RFC)
    if (localPart.length > 64) {
        return [false, 'LOCAL_PART_TOO_LONG'];
    }
    
    // التحقق من أن الجزء المحلي لا يبدأ أو ينتهي بنقطة
    if (localPart.startsWith('.') || localPart.endsWith('.')) {
        return [false, 'INVALID_LOCAL_PART'];
    }
    
    // التحقق من عدم وجود نقطتين متتاليتين في الجزء المحلي
    if (localPart.includes('..')) {
        return [false, 'INVALID_LOCAL_PART'];
    }
    
    // التحقق من أن النطاق لا يبدأ أو ينتهي بنقطة أو شرطة
    if (domainPart.startsWith('.') || domainPart.endsWith('.') || 
        domainPart.startsWith('-') || domainPart.endsWith('-')) {
        return [false, 'INVALID_DOMAIN'];
    }
    
    // التحقق من عدم وجود نقطتين متتاليتين في النطاق
    if (domainPart.includes('..')) {
        return [false, 'INVALID_DOMAIN'];
    }
    
    // محاولة مطابقة الأنماط المختلفة حسب الصرامة
    if (multiDomainPattern.test(email)) {
        // التحقق الإضافي للنطاقات المتعددة
        const domainParts = domainPart.split('.');
        const lastPart = domainParts[domainParts.length - 1];
        
        // التحقق من أن الجزء الأخير من النطاق يحتوي على حرفين على الأقل
        if (lastPart.length < 2) {
            return [false, 'INVALID_TLD'];
        }
        
        // التحقق من أن جميع أجزاء النطاق صالحة
        for (const part of domainParts) {
            if (part.length === 0) {
                return [false, 'INVALID_DOMAIN'];
            }
            // التحقق من أن كل جزء من النطاق لا يبدأ أو ينتهي بشرطة
            if (part.startsWith('-') || part.endsWith('-')) {
                return [false, 'INVALID_DOMAIN'];
            }
        }
        
        return [true, 'MULTI_DOMAIN_PATTERN'];
    }
    
    if (strictPattern.test(email)) {
        return [true, 'STRICT_PATTERN'];
    }
    
    if (basicPattern.test(email)) {
        return [true, 'BASIC_PATTERN'];
    }
    
    if (internationalPattern.test(email)) {
        return [true, 'INTERNATIONAL_PATTERN'];
    }
    
    // إذا لم يطابق أي نمط
    return [false, 'NO_PATTERN_MATCH'];
};

// تصدير الدالة للاستخدام في بيئات Node.js
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { checkEmail };
}