/**
 * storeInfoInHeader اطلاعات ارائه شده را در یک شیء هدر پاسخ HTTP موجود تحت نوع مشخص شده ذخیره می‌کند.
 * این تابع انواع اطلاعات زیر را در نظر می‌گیرد: 'lang'، 'encoding'، 'cache'. آنها به عنوان کلیدهای 'Accept-Language'، 'Accept-Encoding' و 'Cache-Control' به ترتیب ذخیره می‌شوند.
 * محتوای اطلاعات از درخواست‌های کاربر خوانده می‌شود.
 * اگر نوع اطلاعات مشخص شده معتبر باشد، هدر پاسخ به‌روزرسانی شده باید آن را داشته باشد. اگر مشکلی پیش بیاید، تابع باید نقشه هدر اصلی را بدون هیچ تغییری برگرداند.
 *
 * @param {string} infoType نوع اطلاعاتی که باید در هدر ذخیره شود.
 * @param {string} infoContent محتوای اطلاعاتی که باید در هدر ذخیره شود.
 * @param {object} header نقشه هدر پاسخ موجود.
 * @return {object} نقشه هدر پاسخ به‌روزرسانی شده با اطلاعات ذخیره شده.
 */
function storeInfoInHeader(infoType, infoContent, header) {
    const validTypes = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // بررسی اینکه آیا نوع اطلاعات معتبر است
    if (validTypes.hasOwnProperty(infoType)) {
        // ایجاد کپی از هدر برای جلوگیری از تغییرات غیرمنتظره
        const updatedHeader = { ...header };
        
        // به‌روزرسانی هدر با محتوای جدید
        updatedHeader[validTypes[infoType]] = infoContent;
        
        return updatedHeader;
    }

    // در صورت وجود نوع نامعتبر، هدر اصلی را برگردانید
    return header;
}