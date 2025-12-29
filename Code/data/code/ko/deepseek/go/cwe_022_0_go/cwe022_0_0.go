import (
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 경로와 파일명을 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(dirPath, filename)
	
	// 파일 존재 여부 확인
	if _, err := os.Stat(fullPath); os.IsNotExist(err) {
		return ""
	}
	
	// 파일 읽기
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	
	return string(content)
}