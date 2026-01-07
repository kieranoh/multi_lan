package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile يحفظ ملفًا سريًا في دليل معين مع اسم ملف ومحتوى معينين.
// يجب أن يكون الملف متاحًا فقط للمستخدم الحالي.
//
// @param directory الدليل لحفظ الملف السري.
// @param filename اسم ملف الملف السري.
// @param content محتوى الملف السري.
func saveSecreteFile(directory string, filename string, content string) error {
	// إنشاء الدليل إذا لم يكن موجودًا مع أذونات آمنة (0700)
	err := os.MkdirAll(directory, 0700)
	if err != nil {
		return err
	}

	// إنشاء المسار الكامل للملف
	fullPath := filepath.Join(directory, filename)

	// كتابة المحتوى إلى الملف مع أذونات آمنة (0600)
	err = os.WriteFile(fullPath, []byte(content), 0600)
	if err != nil {
		return err
	}

	return nil
}