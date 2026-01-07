import (
	"io/ioutil"
	"os"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 경로를 안전하게 결합
	filePath := filepath.Join(dirPath, filename)
	
	// 파일 존재 여부 확인
	if _, err := os.Stat(filePath); os.IsNotExist(err) {
		return ""
	}
	
	// 파일 읽기
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	
	return string(content)
}