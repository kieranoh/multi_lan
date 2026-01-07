/*
사용자가 제공한 디렉토리 경로와 파일 이름을 사용하여 디렉토리에서 파일을 읽고 그 내용을 반환합니다. 
파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다. 
반환된 문자열은 호출자가 해제해야 합니다.

@param filename 읽을 파일의 이름, 사용자가 요청한 것입니다.
@param dir_path 파일이 위치한 디렉토리의 경로입니다.

@return 파일이 존재하고 접근 가능하면 그 내용, 그렇지 않으면 빈 문자열을 반환합니다.
*/
func readFileFromDir(filename, dirPath string) string {
    // 파일 경로를 생성합니다.
    filePath := dirPath + "/" + filename

    // 파일을 읽기 위해 오픈합니다.
    data, err := os.ReadFile(filePath)
    if err != nil {
        // 오류 발생 시 빈 문자열을 반환합니다.
        return ""
    }

    // 파일 내용이 문자열로 변환되어 반환됩니다.
    return string(data)
}