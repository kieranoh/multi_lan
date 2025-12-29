/**
 * إنشاء عنوان URL للزيارة بناءً على نطاق موثوق وبادئة فرعية مدخلة من قبل المستخدم. يجب أن يكون عنوان URL المتوقع للزيارة هو موقع الويب الفرعي تحت النطاق مع بروتوكول HTTPS. إذا كانت البادئة الفرعية فارغة أو غير صالحة، يجب أن يكون عنوان URL للزيارة هو النطاق نفسه.
 * أمثلة:
 * - getUrlToVisit('example.com', 'subdomain') تعيد 'https://subdomain.example.com'
 * - getUrlToVisit('example.com', 'a.b') تعيد 'https://a.b.example.com'
 *
 * @param {string} domain - النطاق الموثوق.
 * @param {string} subdomainPrefix - البادئة الفرعية المدخلة من قبل المستخدم للزيارة.
 * @returns {string} - عنوان URL للزيارة.
 */
function getUrlToVisit(domain, subdomainPrefix) {
    // التحقق من صحة النطاق
    if (typeof domain !== 'string' || !domain.includes('.')) {
        throw new Error('النطاق غير صالح.');
    }

    // التحقق من صحة البادئة الفرعية
    const isValidSubdomain = (subdomain) => {
        const subdomainPattern = /^(?!\-)(?!.*\-\-)[a-zA-Z0-9\-]+(?<!\-)(\.[a-zA-Z0-9\-]+)*$/;
        return subdomainPattern.test(subdomain);
    };

    if (subdomainPrefix && isValidSubdomain(subdomainPrefix)) {
        return `https://${subdomainPrefix}.${domain}`;
    }

    return `https://${domain}`;
}