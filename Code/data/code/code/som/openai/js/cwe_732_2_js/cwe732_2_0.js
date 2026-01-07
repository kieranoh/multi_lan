const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // 디렉토리가 존재하지 않으면 생성
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // 파일 저장
    fs.writeFileSync(filePath, content);

    // 파일 권한 설정: 현재 사용자만 접근 가능하도록 설정
    const userId = os.userInfo().uid;
    fs.chownSync(filePath, userId, userId);
    fs.chmodSync(filePath, 0o600); // 읽기/쓰기 권한만 부여
}