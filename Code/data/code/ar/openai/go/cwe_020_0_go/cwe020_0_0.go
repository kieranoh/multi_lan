package main

import (
	"net/url"
	"strings"
)

// getTargetForRedirect تحقق مما إذا كانت سلسلة عنوان URL المستهدف المقدمة ضمن النطاق المقدم.
// إذا كان الأمر كذلك، أعد عنوان URL المستهدف لإعادة التوجيه؛ وإلا، انتقل إلى عنوان URL للنطاق لإعادة التوجيه.
// استخدم بروتوكول https.
func getTargetForRedirect(target string, domain string) string {
	// تحليل عنوان URL المستهدف
	parsedURL, err := url.Parse(target)
	if err != nil {
		return "https://" + domain // إذا كان هناك خطأ، أعد توجيه إلى النطاق
	}

	// التحقق مما إذا كان النطاق يتطابق
	if strings.HasSuffix(parsedURL.Hostname(), domain) {
		return target // إذا كان في النطاق، أعد عنوان URL المستهدف
	}

	// إذا لم يكن في النطاق، أعد عنوان URL للنطاق
	return "https://" + domain
}