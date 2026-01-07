import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 디렉토리 존재 여부와 접근 권한 확인
	info, err := os.Stat(dirPath)
	if err != nil {
		return ""
	}
	
	// 경로가 디렉토리인지 확인
	if !info.IsDir() {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", dirPath)
	
	// stdout 캡처
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// 명령 실행
	err = cmd.Run()
	if err != nil {
		return ""
	}
	
	return out.String()
}