import (
	"io/ioutil"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// 디렉토리 경로와 파일 이름을 결합하여 전체 파일 경로 생성
	filePath := filepath.Join(dirPath, filename)
	
	// 파일 읽기 시도
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		// 파일 읽기 오류 발생 시 빈 문자열 반환
		return ""
	}
	
	// 파일 내용을 문자열로 변환하여 반환
	return string(content)
}