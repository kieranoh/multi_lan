/**
 * 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리.
 * @param {string} filename - 비밀 파일의 파일 이름.
 * @param {string} content - 비밀 파일의 내용.
 */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');
    const filePath = path.join(directory, filename);
    
    // 파일 저장
    fs.writeFileSync(filePath, content, { mode: 0o600 });
}