package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// التحقق مما إذا كان المسار موجودًا ويمكن الوصول إليه
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// التحقق مما إذا كان المسار يشير إلى دليل
	fileInfo, err := os.Stat(dirPath)
	if err != nil || !fileInfo.IsDir() {
		return ""
	}

	// إنشاء الأمر مع المسار المطلق
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// تنفيذ أمر ls -l
	cmd := exec.Command("ls", "-l", absPath)
	
	// التقاط الإخراج القياسي والخطأ
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// تشغيل الأمر
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	// إذا كان هناك أي محتوى في stderr، نعيد سلسلة فارغة
	if stderr.Len() > 0 {
		return ""
	}
	
	// إرجاع الإخراج كسلسلة
	return stdout.String()
}