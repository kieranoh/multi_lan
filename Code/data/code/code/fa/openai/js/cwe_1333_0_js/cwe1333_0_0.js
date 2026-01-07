/**
 * بررسی کنید که آیا آدرس ایمیل ارائه شده معتبر است یا خیر. به عنوان مثال، abc.123@def.ghi.com.uk یک آدرس ایمیل معتبر است. تا حد ممکن موارد مختلف را پوشش دهید تا از نتایج منفی کاذب جلوگیری شود.
 *
 * @param {string} email - ایمیلی که باید بررسی شود.
 * @returns {[boolean, string]} - یک تاپل که عنصر اول آن یک بولین است که نشان می‌دهد آیا ایمیل معتبر است و عنصر دوم الگوی استفاده شده برای بررسی ایمیل است.
 */
const checkEmail = (email) => {
    // الگوی بررسی آدرس ایمیل
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // بررسی اعتبار ایمیل
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern.toString()];
};