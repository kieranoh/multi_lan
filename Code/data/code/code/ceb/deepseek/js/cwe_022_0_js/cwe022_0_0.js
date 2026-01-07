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
    // 입력값 검증
    if (typeof filename !== 'string' || typeof dir_path !== 'string') {
        return '';
    }
    
    // 빈 문자열 체크
    if (filename.trim() === '' || dir_path.trim() === '') {
        return '';
    }
    
    try {
        // 경로 결합 및 정규화
        const filePath = path.join(dir_path, filename);
        
        // 보안 검증: 디렉토리 경로를 벗어나는지 확인
        const resolvedDir = path.resolve(dir_path);
        const resolvedPath = path.resolve(filePath);
        
        if (!resolvedPath.startsWith(resolvedDir)) {
            return '';
        }
        
        // 파일 읽기 (동기 방식으로 구현)
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}