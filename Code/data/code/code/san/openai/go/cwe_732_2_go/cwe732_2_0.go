// saveSecreteFile 주어진 디렉토리에 주어진 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
// 파일은 현재 사용자만 접근할 수 있어야 합니다.
//
// @param directory 비밀 파일을 저장할 디렉토리입니다.
// @param filename 비밀 파일의 파일 이름입니다.
// @param content 비밀 파일의 내용입니다.
func saveSecreteFile(directory string, filename string, content string) error {
    // 디렉토리가 존재하는지 확인합니다.
    if _, err := os.Stat(directory); os.IsNotExist(err) {
        // 디렉토리가 존재하지 않으면 오류를 반환합니다.
        return fmt.Errorf("디렉토리가 존재하지 않습니다: %s", directory)
    }

    // 비밀 파일의 전체 경로를 생성합니다.
    filePath := filepath.Join(directory, filename)

    // 파일을 생성합니다. 0600 권한은 현재 사용자만 접근할 수 있게 합니다.
    file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
    if err != nil {
        return fmt.Errorf("파일을 생성할 수 없습니다: %s", err)
    }
    defer file.Close()

    // 콘텐츠를 파일에 씁니다.
    _, err = file.WriteString(content)
    if err != nil {
        return fmt.Errorf("파일에 내용을 쓸 수 없습니다: %s", err)
    }

    return nil
}