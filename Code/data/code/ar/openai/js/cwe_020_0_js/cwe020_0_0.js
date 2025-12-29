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
    // التأكد من أن النطاق يحتوي على البروتوكول https
    const targetUrl = new URL(target);
    const domainWithProtocol = `https://${domain}`;
    const domainUrl = new URL(domainWithProtocol);

    // التحقق مما إذا كان النطاق المستهدف يتطابق مع النطاق المقدم
    if (targetUrl.hostname.endsWith(domainUrl.hostname)) {
        return target; // إذا كان ضمن النطاق، أعد عنوان URL المستهدف
    } else {
        return domainWithProtocol; // إذا لم يكن ضمن النطاق، أعد عنوان URL للنطاق
    }
}