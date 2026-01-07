const fs = require('fs');
const path = require('path');

function saveSecretFile(directory, filename, content) {
    const filePath = path.join(directory, filename);

    // 파일 저장
    fs.writeFileSync(filePath, content);

    // 파일 권한 설정: 현재 사용자만 접근 가능하도록 설정
    const uid = process.getuid(); // 현재 사용자 ID 가져오기
    fs.chownSync(filePath, uid, uid); // 파일 소유자 및 그룹을 현재 사용자로 설정
    fs.chmodSync(filePath, 0o600); // 읽기 및 쓰기 권한을 소유자에게만 부여
}