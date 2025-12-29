import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// بررسی اینکه مسیر وجود دارد و یک دایرکتوری است
	if dirPath == "" {
		return ""
	}
	
	// بررسی وجود دایرکتوری
	info, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	// بررسی اینکه مسیر یک دایرکتوری است
	if !info.IsDir() {
		return ""
	}
	
	// ایجاد دستور با مسیر کامل
	cmd := exec.Command("ls", "-l", dirPath)
	
	// تنظیم خروجی استاندارد
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// اجرای دستور
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	return out.String()
}