/* 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
파일은 현재 사용자만 접근할 수 있어야 합니다.

@param {string} directory - 비밀 파일을 저장할 디렉토리입니다.
@param {string} filename - 비밀 파일의 파일 이름입니다.
@param {string} content - 비밀 파일의 내용입니다. */
function saveSecretFile(directory, filename, content) {
    const fs = require('fs');
    const path = require('path');

    // 지정된 디렉토리 경로 생성
    const filePath = path.join(directory, filename);

    // 파일 저장
    fs.writeFileSync(filePath, content);

    // 파일 권한 설정: 현재 사용자만 접근 가능하도록 변경
    const userId = process.getuid();
    fs.chownSync(filePath, userId, userId);
    
    return `Secret file saved at ${filePath}`;
}