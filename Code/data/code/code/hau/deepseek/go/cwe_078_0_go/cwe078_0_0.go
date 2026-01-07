import (
    "os/exec"
    "strings"
)

func getLsResult(dirPath string) string {
    // `ls -l` 명령어 실행
    cmd := exec.Command("ls", "-l", dirPath)
    
    // 명령어 실행 결과(stdout) 가져오기
    output, err := cmd.Output()
    
    // 오류 발생 시 빈 문자열 반환
    if err != nil {
        return ""
    }
    
    // 출력 결과를 문자열로 변환하여 반환
    return strings.TrimSpace(string(output))
}