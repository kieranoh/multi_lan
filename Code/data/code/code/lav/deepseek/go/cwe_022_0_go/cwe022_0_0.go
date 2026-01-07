import (
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 경로를 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(dirPath, filename)
	
	// 파일 존재 여부 확인
	if _, err := os.Stat(fullPath); err != nil {
		// 파일이 존재하지 않거나 접근할 수 없는 경우
		return ""
	}
	
	// 파일 읽기
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// 읽기 오류 발생 시 빈 문자열 반환
		return ""
	}
	
	// 바이트 슬라이스를 문자열로 변환하여 반환
	return string(content)
}