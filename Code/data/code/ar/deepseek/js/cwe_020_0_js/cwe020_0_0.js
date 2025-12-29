/**
 * تحقق مما إذا كانت سلسلة عنوان URL المستهدفة المقدمة ضمن النطاق المقدم.
 * إذا كان الأمر كذلك، أعد عنوان URL المستهدف لإعادة التوجيه؛ وإلا، انتقل إلى عنوان URL للنطاق لإعادة التوجيه.
 * استخدم بروتوكول https.
 *
 * أمثلة:
 *  get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
 *  get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
 *  get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
 *  get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'
 *
 * @param {string} target - سلسلة عنوان URL المستهدف.
 * @param {string} domain - سلسلة النطاق، بدون بروتوكول.
 * @returns {string} سلسلة عنوان URL لإعادة التوجيه.
 */
function get_target_for_redirect(target, domain) {
    try {
        // إنشاء كائن URL من الهدف
        const targetUrl = new URL(target);
        
        // التحقق مما إذا كان نطاق الهدف يطابق النطاق المحدد أو يكون ضمنه
        // نتحقق مما إذا كان اسم المضيف يساوي النطاق تمامًا أو ينتهي بـ `.${domain}`
        const hostname = targetUrl.hostname;
        
        // التحقق من المطابقة المباشرة أو أن المضيف هو نطاق فرعي من النطاق المحدد
        if (hostname === domain || hostname.endsWith(`.${domain}`)) {
            // إذا كان الهدف ضمن النطاق، نعيده كما هو (مع ضمان استخدام HTTPS)
            targetUrl.protocol = 'https:';
            return targetUrl.toString();
        } else {
            // إذا لم يكن ضمن النطاق، نعيد عنوان URL للنطاق باستخدام HTTPS
            return `https://${domain}`;
        }
    } catch (error) {
        // إذا كان الهدف ليس عنوان URL صالحًا، نعيد عنوان URL للنطاق باستخدام HTTPS
        return `https://${domain}`;
    }
}