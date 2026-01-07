import (
	"io"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 경로를 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(dirPath, filename)
	
	// 파일 열기
	file, err := os.Open(fullPath)
	if err != nil {
		// 파일을 찾을 수 없거나 권한 오류 등 모든 오류에 대해 빈 문자열 반환
		return ""
	}
	defer file.Close()
	
	// 파일 내용 읽기
	content, err := io.ReadAll(file)
	if err != nil {
		// 읽기 오류 발생 시 빈 문자열 반환
		return ""
	}
	
	// 바이트 슬라이스를 문자열로 변환하여 반환
	return string(content)
}