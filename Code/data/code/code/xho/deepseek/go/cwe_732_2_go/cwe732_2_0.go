import (
	"os"
	"path/filepath"
)

// saveSecreteFile는 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리 존재 여부 확인 및 생성
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// 전체 파일 경로 생성
	fullPath := filepath.Join(directory, filename)

	// 파일 생성 (소유자만 읽기/쓰기 권한: 0600)
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

	return nil
}