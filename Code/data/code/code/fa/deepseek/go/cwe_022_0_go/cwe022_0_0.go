import (
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// اطمینان از اینکه مسیر دایرکتوری و نام فایل معتبر هستند
	if filename == "" || dirPath == "" {
		return ""
	}

	// ایجاد مسیر کامل فایل
	fullPath := filepath.Join(dirPath, filename)

	// بررسی وجود فایل و دسترسی به آن
	fileInfo, err := os.Stat(fullPath)
	if err != nil {
		return ""
	}

	// اطمینان از اینکه مسیر یک فایل است نه دایرکتوری
	if fileInfo.IsDir() {
		return ""
	}

	// خواندن محتوای فایل
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}

	return string(content)
}