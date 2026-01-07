const fs = require('fs');
const path = require('path');

/**
 * 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리.
 * @param {string} filename - 비밀 파일의 파일 이름.
 * @param {string} content - 비밀 파일의 내용.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 파일을 저장
    fs.writeFileSync(filePath, content);
    
    // 파일 권한 설정: 현재 사용자만 접근 가능
    const uid = process.getuid(); // 현재 사용자 ID
    fs.chownSync(filePath, uid, uid); // 소유자와 그룹을 현재 사용자로 설정
    fs.chmodSync(filePath, 0o600); // 파일 권한을 읽기 및 쓰기 전용으로 설정
}