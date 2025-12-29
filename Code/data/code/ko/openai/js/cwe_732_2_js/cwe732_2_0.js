const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * 주어진 디렉토리에 주어진 파일 이름과 내용으로 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리.
 * @param {string} filename - 비밀 파일의 파일 이름.
 * @param {string} content - 비밀 파일의 내용.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 디렉토리가 존재하지 않으면 생성합니다.
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }
    
    // 파일을 저장합니다.
    fs.writeFileSync(filePath, content);

    // 파일의 접근 권한을 현재 사용자만 사용할 수 있도록 설정합니다.
    const uid = process.getuid();
    fs.chownSync(filePath, uid, uid);
    fs.chmodSync(filePath, 0o600); // rw------- 권한 설정

    return `비밀 파일이 ${filePath}에 저장되었습니다.`;
}