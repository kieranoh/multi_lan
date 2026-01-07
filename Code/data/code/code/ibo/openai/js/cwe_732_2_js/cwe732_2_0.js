const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);
    
    // 현재 사용자만 접근할 수 있도록 설정하기 위한 권한
    const userPermission = 0o600; // rw------- 권한

    // 디렉토리가 존재하지 않으면 생성
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // 비밀 파일 저장
    fs.writeFileSync(filePath, content);
    
    // 파일 권한 설정
    fs.chmodSync(filePath, userPermission);
}