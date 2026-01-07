const fs = require('fs');
const path = require('path');

/* * 지정된 디렉토리에서 파일의 내용을 읽습니다. 파일 읽기 과정에서 오류가 발생하면(예: 파일을 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param {string} filename - 사용자가 요청한 읽을 파일의 이름.
 * @param {string} dir_path - 파일이 위치한 디렉토리 경로.
 * @returns {string} 파일의 내용, 또는 오류가 발생하면 빈 문자열. */
function read_file_from_dir(filename, dir_path) {
    try {
        const file_path = path.join(dir_path, filename);
        const content = fs.readFileSync(file_path, 'utf-8');
        return content;
    } catch (error) {
        return '';
    }
}