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
	// باز کردن فایل tar
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// تشخیص فشرده‌سازی gzip
	var tarReader *tar.Reader
	if strings.HasSuffix(tarPath, ".tar.gz") || strings.HasSuffix(tarPath, ".tgz") {
		gzReader, err := gzip.NewReader(file)
		if err != nil {
			return false
		}
		defer gzReader.Close()
		tarReader = tar.NewReader(gzReader)
	} else if strings.HasSuffix(tarPath, ".tar") {
		tarReader = tar.NewReader(file)
	} else {
		// اگر پسوند فایل شناخته شده نیست، سعی می‌کنیم آن را به عنوان tar ساده بخوانیم
		tarReader = tar.NewReader(file)
	}

	// ایجاد پوشه مقصد اگر وجود ندارد
	if err := os.MkdirAll(destPath, 0755); err != nil {
		return false
	}

	// استخراج فایل‌ها
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // پایان فایل
		}
		if err != nil {
			return false
		}

		// اطمینان از امنیت مسیر فایل
		targetPath := filepath.Join(destPath, header.Name)
		if !strings.HasPrefix(targetPath, filepath.Clean(destPath)+string(os.PathSeparator)) {
			return false // تلاش برای استخراج خارج از پوشه مقصد
		}

		// بررسی نوع فایل
		switch header.Typeflag {
		case tar.TypeDir:
			// ایجاد پوشه
			if err := os.MkdirAll(targetPath, os.FileMode(header.Mode)); err != nil {
				return false
			}
		case tar.TypeReg, tar.TypeRegA:
			// ایجاد فایل
			if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
				return false
			}
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		case tar.TypeSymlink:
			// ایجاد پیوند نمادین
			if err := os.Symlink(header.Linkname, targetPath); err != nil {
				return false
			}
		case tar.TypeLink:
			// ایجاد پیوند سخت
			linkTarget := filepath.Join(destPath, header.Linkname)
			if err := os.Link(linkTarget, targetPath); err != nil {
				return false
			}
		default:
			// نادیده گرفتن انواع دیگر (مانند دستگاه‌ها، سوکت‌ها و غیره)
			continue
		}

		// تنظیم زمان‌های دسترسی و تغییر
		if err := os.Chtimes(targetPath, header.AccessTime, header.ModTime); err != nil {
			// اگر تنظیم زمان‌ها شکست خورد، ادامه می‌دهیم اما استخراج را متوقف نمی‌کنیم
			continue
		}
	}

	return true
}