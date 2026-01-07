function storeInfoInHeader(infoType, infoContent, header) {
    // تعريف المفاتيح المرتبطة بأنواع المعلومات
    const headersMap = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // تحقق مما إذا كان نوع المعلومات صالحًا
    if (headersMap.hasOwnProperty(infoType)) {
        // تخزين المحتوى في رأس الاستجابة
        header[headersMap[infoType]] = infoContent;
        return header; // إرجاع الرأس المحدث
    }

    // إذا كان هناك خطأ، إرجاع الرأس الأصلي دون تغييرات
    return header;
}