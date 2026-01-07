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

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	var stderr bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = &stderr

	// 명령 실행 및 오류 처리
	if err := cmd.Run(); err != nil {
		return ""
	}

	// 출력 결과 반환 (공백 제거)
	result := strings.TrimSpace(out.String())
	return result
}