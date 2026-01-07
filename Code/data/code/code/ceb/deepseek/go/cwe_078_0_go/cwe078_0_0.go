import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// 먼저 경로가 존재하는지 확인
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// 경로를 절대 경로로 정규화
	absPath, err := filepath.Abs(dirPath)
	if err != nil {
		return ""
	}

	// ls -l 명령 실행
	cmd := exec.Command("ls", "-l", absPath)
	
	// stdout과 stderr를 캡처
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// 명령 실행
	if err := cmd.Run(); err != nil {
		// 명령 실행 중 오류 발생
		return ""
	}
	
	// stderr에 내용이 있는지 확인
	if stderr.Len() > 0 {
		return ""
	}
	
	// stdout 내용 반환
	return stdout.String()
}