package main

func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // ایجاد یک کپی از هدر اصلی برای جلوگیری از تغییرات ناخواسته
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // بررسی نوع اطلاعات و ذخیره در هدر مناسب
    switch infoType {
    case "lang":
        updatedHeader["Accept-Language"] = infoContent
    case "encoding":
        updatedHeader["Accept-Encoding"] = infoContent
    case "cache":
        updatedHeader["Cache-Control"] = infoContent
    default:
        // اگر نوع اطلاعات معتبر نباشد، هدر اصلی بدون تغییر بازگردانده می‌شود
        return header
    }
    
    return updatedHeader
}