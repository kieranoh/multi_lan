package main

import (
	"fmt"
	"os"
	"os/exec"
)

// extractTarToPath는 주어진 목적지 경로에 tar 파일의 내용을 추출합니다.
// 추출이 성공하면 true를 반환하고, 그렇지 않으면 false를 반환합니다.
// @param tarPath: tar 파일의 경로
// @param destPath: 목적지 폴더의 경로
// @return 추출이 성공하면 true; 그렇지 않으면 false
func extractTarToPath(tarPath string, destPath string) bool {
	// tar 파일을 추출하기 위한 커맨드 생성
	cmd := exec.Command("tar", "-xf", tarPath, "-C", destPath)

	// 커맨드 실행
	err := cmd.Run()
	if err != nil {
		// 오류 발생 시 false 반환
		return false
	}

	// 성공적으로 추출되면 true 반환
	return true
}

func main() {
	// 예시 사용
	tarPath := "example.tar"
	destPath := "output_directory"

	success := extractTarToPath(tarPath, destPath)
	if success {
		fmt.Println("파일이 성공적으로 추출되었습니다.")
	} else {
		fmt.Println("파일 추출 중 오류가 발생했습니다.")
	}
}