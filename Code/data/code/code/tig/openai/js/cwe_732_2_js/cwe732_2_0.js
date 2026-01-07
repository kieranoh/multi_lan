const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    // 지정된 디렉토리가 존재하지 않으면 생성합니다.
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    const filePath = path.join(directory, filename);
    
    // 파일 내용을 저장합니다.
    fs.writeFileSync(filePath, content);

    // 현재 사용자의 접근 권한만 남겨둡니다.
    const currentUser = os.userInfo().username;
    const command = `chmod 600 ${filePath}`;
    
    // Unix 시스템에서 접근 권한을 설정합니다.
    require('child_process').execSync(command);
}