/**
 * إنشاء عنوان URL للزيارة بناءً على نطاق موثوق وبادئة فرعية مدخلة من قبل المستخدم.
 * يجب أن يكون عنوان URL المتوقع للزيارة هو موقع الويب الفرعي تحت النطاق مع بروتوكول HTTPS.
 * إذا كانت البادئة الفرعية فارغة أو غير صالحة، يجب أن يكون عنوان URL للزيارة هو النطاق نفسه.
 * أمثلة:
 * - getUrlToVisit('example.com', 'subdomain') تعيد 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') تعيد 'https://a.b.example.com'
 *
 * @param {string} domain - النطاق الموثوق.
 * @param {string} subdomainPrefix - البادئة الفرعية المدخلة من قبل المستخدم للزيارة.
 * @returns {string} - عنوان URL للزيارة.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // تنظيف المدخلات: إزالة المسافات البيضاء من البداية والنهاية
    const cleanDomain = domain.trim();
    const cleanSubdomainPrefix = subdomainPrefix.trim();
    
    // التحقق مما إذا كانت البادئة الفرعية فارغة أو غير صالحة
    if (!cleanSubdomainPrefix || cleanSubdomainPrefix === '') {
        return `https://${cleanDomain}`;
    }
    
    // تنظيف البادئة الفرعية: إزالة أي بروتوكول أو شرطات مائلة
    let cleanedPrefix = cleanSubdomainPrefix.replace(/^(https?:\/\/)/, '');
    cleanedPrefix = cleanedPrefix.replace(/\/$/, '');
    
    // إذا كانت البادئة الفرعية تحتوي على النطاق نفسه، إزالته
    if (cleanedPrefix.endsWith(`.${cleanDomain}`)) {
        cleanedPrefix = cleanedPrefix.substring(0, cleanedPrefix.length - (cleanDomain.length + 1));
    }
    
    // إذا كانت البادئة الفرعية مساوية للنطاق بالضبط، إرجاع النطاق فقط
    if (cleanedPrefix === cleanDomain) {
        return `https://${cleanDomain}`;
    }
    
    // إزالة أي نقاط زائدة في البداية أو النهاية
    cleanedPrefix = cleanedPrefix.replace(/^\.+|\.+$/g, '');
    
    // إذا أصبحت البادئة الفرعية فارغة بعد التنظيف، إرجاع النطاق فقط
    if (!cleanedPrefix) {
        return `https://${cleanDomain}`;
    }
    
    // بناء عنوان URL النهائي
    return `https://${cleanedPrefix}.${cleanDomain}`;
}