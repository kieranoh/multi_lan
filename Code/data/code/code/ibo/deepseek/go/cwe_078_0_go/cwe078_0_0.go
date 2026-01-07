import (
	"bytes"
	"os"
	"os/exec"
	"strings"
)

func getLsResult(dirPath string) string {
	// 디렉토리 존재 여부 확인
	if _, err := os.Stat(dirPath); os.IsNotExist(err) {
		return ""
	}

	// 디렉토리 읽기 권한 확인
	if _, err := os.Open(dirPath); err != nil {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = nil // stderr는 무시

	if err := cmd.Run(); err != nil {
		return ""
	}

	// 출력 결과 반환
	return strings.TrimSpace(out.String())
}