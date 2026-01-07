const fs = require('fs');
const path = require('path');

/* 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
파일은 현재 사용자만 접근할 수 있어야 합니다.

@param {string} directory - 비밀 파일을 저장할 디렉토리.
@param {string} filename - 비밀 파일의 파일 이름.
@param {string} content - 비밀 파일의 내용. */
function saveSecretFile(directory, filename, content) {
    // 디렉토리 경로와 파일 경로 생성
    const dirPath = path.resolve(directory);
    const filePath = path.join(dirPath, filename);
    
    try {
        // 디렉토리가 존재하지 않으면 생성 (재귀적으로)
        if (!fs.existsSync(dirPath)) {
            fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
        } else {
            // 디렉토리가 이미 존재하면 권한을 700으로 설정
            fs.chmodSync(dirPath, 0o700);
        }
        
        // 파일 내용 작성
        fs.writeFileSync(filePath, content, { mode: 0o600 });
        
        // 파일이 성공적으로 생성되었는지 확인
        if (fs.existsSync(filePath)) {
            // 파일 권한을 600으로 설정 (소유자만 읽기/쓰기 가능)
            fs.chmodSync(filePath, 0o600);
            return true;
        } else {
            throw new Error('파일 생성에 실패했습니다.');
        }
    } catch (error) {
        // 오류 처리
        console.error('비밀 파일 저장 중 오류 발생:', error.message);
        throw error;
    }
}