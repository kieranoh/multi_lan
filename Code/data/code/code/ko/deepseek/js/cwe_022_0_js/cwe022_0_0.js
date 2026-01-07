const fs = require('fs');
const path = require('path');

/**
 * 지정된 디렉토리에서 파일의 내용을 읽습니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param {string} filename - 사용자가 요청한 읽을 파일의 이름입니다.
 * @param {string} dir_path - 파일이 위치한 디렉토리 경로입니다.
 * @returns {string} 파일의 내용 또는 오류가 발생하면 빈 문자열입니다.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        // 경로를 안전하게 결합
        const filePath = path.join(dir_path, filename);
        
        // 파일 존재 여부 확인
        if (!fs.existsSync(filePath)) {
            return '';
        }
        
        // 파일 읽기 (동기적으로 처리)
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // 모든 종류의 파일 읽기 오류를 처리
        return '';
    }
}