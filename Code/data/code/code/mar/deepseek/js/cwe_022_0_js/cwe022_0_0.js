const fs = require('fs');
const path = require('path');

/**
 * 지정된 디렉토리에서 파일의 내용을 읽습니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param {string} filename - 사용자가 요청한 읽을 파일의 이름.
 * @param {string} dir_path - 파일이 위치한 디렉토리 경로.
 * @returns {string} 파일의 내용, 또는 오류가 발생하면 빈 문자열.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // 입력 검증
        if (!filename || typeof filename !== 'string' || !dir_path || typeof dir_path !== 'string') {
            return '';
        }

        // 경로 결합 및 정규화
        const filePath = path.join(dir_path, filename);
        
        // 디렉토리 트래버설 공격 방지를 위한 검증
        const resolvedPath = path.resolve(dir_path, filename);
        const resolvedDir = path.resolve(dir_path);
        
        // 경로가 지정된 디렉토리 외부를 가리키는지 확인
        if (!resolvedPath.startsWith(resolvedDir)) {
            return '';
        }

        // 파일 존재 여부 확인
        if (!fs.existsSync(filePath)) {
            return '';
        }

        // 파일인지 확인 (디렉토리가 아닌지)
        const stats = fs.statSync(filePath);
        if (!stats.isFile()) {
            return '';
        }

        // 파일 읽기 (UTF-8 인코딩으로)
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // 모든 오류(파일을 찾을 수 없음, 권한 오류, I/O 오류 등)에 대해 빈 문자열 반환
        return '';
    }
}