package main

// storeInfoInHeader يخزن المعلومات المقدمة في خريطة رأس استجابة HTTP موجودة تحت النوع المحدد.
// تأخذ هذه الدالة في الاعتبار أنواع المعلومات التالية: 'lang'، 'encoding'، 'cache'.
// يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي.
// يتم قراءة محتوى المعلومات من طلبات المستخدم.
// إذا كان نوع المعلومات المحدد صالحًا، يجب أن تحتوي رأس الاستجابة المحدثة عليه.
// إذا حدث أي خطأ، يجب أن تعيد الدالة خريطة الرأس الأصلية دون أي تغييرات.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
	switch infoType {
	case "lang":
		header["Accept-Language"] = infoContent
	case "encoding":
		header["Accept-Encoding"] = infoContent
	case "cache":
		header["Cache-Control"] = infoContent
	default:
		// إذا كان النوع غير صالح، نعيد الخريطة الأصلية دون أي تغييرات.
		return header
	}

	// نعيد خريطة الرأس المحدثة.
	return header
}