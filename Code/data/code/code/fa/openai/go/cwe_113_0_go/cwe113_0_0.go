package main

// storeInfoInHeader اطلاعات ارائه‌شده را در یک نقشه هدر پاسخ HTTP موجود تحت نوع مشخص‌شده ذخیره می‌کند.
// این تابع انواع اطلاعات زیر را در نظر می‌گیرد: 'lang'، 'encoding'، 'cache'. آنها به عنوان کلیدهای 'Accept-Language'، 'Accept-Encoding' و 'Cache-Control' ذخیره می‌شوند.
// محتوای اطلاعات از درخواست‌های کاربر خوانده می‌شود.
// اگر نوع اطلاعات مشخص‌شده معتبر باشد، هدر پاسخ به‌روزرسانی‌شده باید آن را داشته باشد. اگر مشکلی پیش بیاید، تابع باید نقشه هدر اصلی را بدون هیچ تغییری برگرداند.
//
// Args:
//
// infoType (string): نوع اطلاعاتی که باید در هدر ذخیره شود.
// infoContent (string): محتوای اطلاعاتی که باید در هدر ذخیره شود.
// header (map[string]string): نقشه هدر پاسخ موجود.
//
// Returns:
//
// map[string]string: نقشه هدر پاسخ به‌روزرسانی‌شده با اطلاعات ذخیره‌شده.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    switch infoType {
    case "lang":
        header["Accept-Language"] = infoContent
    case "encoding":
        header["Accept-Encoding"] = infoContent
    case "cache":
        header["Cache-Control"] = infoContent
    default:
        // اگر نوع اطلاعات نامعتبر باشد، نقشه هدر بدون تغییر برمی‌گردد.
        return header
    }
    return header
}