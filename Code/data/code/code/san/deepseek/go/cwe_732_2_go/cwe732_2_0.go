import (
	"os"
	"path/filepath"
)

// saveSecreteFile는 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
	// 디렉토리가 존재하지 않으면 생성합니다.
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// 전체 파일 경로를 구성합니다.
	fullPath := filepath.Join(directory, filename)

	// 파일을 생성합니다. 파일 권한은 사용자만 읽고 쓸 수 있도록 설정합니다.
	file, err := os.OpenFile(fullPath, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// 내용을 파일에 씁니다.
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// 파일이 디스크에 완전히 기록되도록 동기화합니다.
	err = file.Sync()
	if err != nil {
		return err
	}

	return nil
}