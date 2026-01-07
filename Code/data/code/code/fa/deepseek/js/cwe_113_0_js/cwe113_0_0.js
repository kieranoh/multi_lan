/**
 * اطلاعات ارائه شده را در یک شیء هدر پاسخ HTTP موجود تحت نوع مشخص شده ذخیره می‌کند.
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
    // ایجاد یک کپی از هدر اصلی برای جلوگیری از تغییرات ناخواسته
    const updatedHeader = { ...header };
    
    // تعیین کلید هدر بر اساس نوع اطلاعات
    let headerKey;
    switch (infoType) {
        case 'lang':
            headerKey = 'Accept-Language';
            break;
        case 'encoding':
            headerKey = 'Accept-Encoding';
            break;
        case 'cache':
            headerKey = 'Cache-Control';
            break;
        default:
            // اگر نوع اطلاعات معتبر نباشد، هدر اصلی را بدون تغییر برگردان
            return header;
    }
    
    // بررسی اینکه infoContent یک رشته غیر خالی باشد
    if (typeof infoContent !== 'string' || infoContent.trim() === '') {
        return header;
    }
    
    // ذخیره اطلاعات در هدر
    updatedHeader[headerKey] = infoContent;
    
    return updatedHeader;
}