import (
	"os"
	"path/filepath"
)

// 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리.
// @param filename 비밀 파일의 파일 이름.
// @param content 비밀 파일의 내용.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 경로와 파일명을 결합하여 전체 파일 경로 생성
	fullPath := filepath.Join(directory, filename)
	
	// 파일 생성 (권한: 사용자만 읽기/쓰기 가능)
	file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()
	
	// 내용 쓰기
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}
	
	// 파일 동기화하여 디스크에 즉시 저장
	err = file.Sync()
	if err != nil {
		return err
	}
	
	return nil
}