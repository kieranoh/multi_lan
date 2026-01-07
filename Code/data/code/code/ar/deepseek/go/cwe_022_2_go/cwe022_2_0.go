package main

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

func extractTarToPath(tarPath string, destPath string) bool {
	// فتح ملف tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// محاولة فك الضغط إذا كان ملف tar مضغوطًا (tar.gz)
	var tarReader *tar.Reader
	if strings.HasSuffix(strings.ToLower(tarPath), ".gz") ||
		strings.HasSuffix(strings.ToLower(tarPath), ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else {
		tarReader = tar.NewReader(file)
	}

	// استخراج كل ملف في الأرشيف
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // نهاية الملف
		}
		if err != nil {
			return false
		}

		// بناء مسار الملف الهدف
		targetPath := filepath.Join(destPath, header.Name)

		// التحقق من أن المسار يقع ضمن مجلد الوجهة (أمان)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false
		}

		// معالجة نوع الملف
		switch header.Typeflag {
		case tar.TypeDir:
			// إنشاء المجلد
			if err := os.MkdirAll(targetPath, 0755); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// إنشاء المجلدات الأم إذا لزم الأمر
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}

			// إنشاء الملف
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}

			// نسخ محتوى الملف
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// إنشاء رابط رمزي
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// إنشاء رابط صلب
			linkPath := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkPath, targetPath); err != nil {
				return false
			}
		default:
			// تخطي أنواع الملفات غير المدعومة
			continue
		}
	}

	return true
}