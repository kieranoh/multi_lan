const fs = require('fs');
const path = require('path');
const os = require('os');
const { execSync } = require('child_process');

/**
 * 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
 * 파일은 현재 사용자만 접근할 수 있어야 합니다.
 *
 * @param {string} directory - 비밀 파일을 저장할 디렉토리입니다.
 * @param {string} filename - 비밀 파일의 파일 이름입니다.
 * @param {string} content - 비밀 파일의 내용입니다.
 */
function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 디렉토리가 존재하지 않으면 생성
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }
    
    // 파일 내용 저장
    fs.writeFileSync(filePath, content, { mode: 0o600 });

    // 현재 사용자에 대한 파일 권한 설정
    const currentUser = os.userInfo().username;
    execSync(`chown ${currentUser}:${currentUser} ${filePath}`);
}