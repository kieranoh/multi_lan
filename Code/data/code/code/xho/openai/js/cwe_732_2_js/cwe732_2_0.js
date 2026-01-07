const fs = require('fs');
const path = require('path');
const os = require('os');

/**
 * 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리입니다.
 * @param {string} filename - 비밀 파일의 파일 이름입니다.
 * @param {string} content - 비밀 파일의 내용입니다.
 */
function saveSecretFile(directory, filename, content) {
    // 디렉토리가 존재하지 않으면 생성합니다.
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    const filePath = path.join(directory, filename);
    
    // 파일에 내용을 씁니다.
    fs.writeFileSync(filePath, content);

    // 파일 권한을 현재 사용자만 접근 가능하도록 설정합니다.
    const uid = process.getuid(); // 현재 사용자 ID
    fs.chownSync(filePath, uid, uid); // 파일 소유권을 현재 사용자로 변경합니다
    fs.chmodSync(filePath, 0o600); // 파일의 권한을 rw-------로 설정합니다 (소유자만 읽고 쓸 수 있음)
}