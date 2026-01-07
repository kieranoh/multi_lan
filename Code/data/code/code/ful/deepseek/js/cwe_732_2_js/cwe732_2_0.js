const fs = require('fs');
const path = require('path');

/* 지정된 디렉토리에 지정된 파일 이름과 내용을 가진 비밀 파일을 저장합니다.
파일은 현재 사용자만 접근할 수 있어야 합니다.

@param {string} directory - 비밀 파일을 저장할 디렉토리.
@param {string} filename - 비밀 파일의 파일 이름.
@param {string} content - 비밀 파일의 내용. */
function saveSecretFile(directory, filename, content) {
    // 디렉토리 경로와 파일 경로를 생성합니다.
    const dirPath = path.resolve(directory);
    const filePath = path.join(dirPath, filename);

    try {
        // 디렉토리가 존재하지 않으면 생성합니다.
        if (!fs.existsSync(dirPath)) {
            fs.mkdirSync(dirPath, { recursive: true, mode: 0o700 });
        } else {
            // 디렉토리가 이미 존재하면 권한을 확인하고 필요시 수정합니다.
            const dirStats = fs.statSync(dirPath);
            if ((dirStats.mode & 0o777) !== 0o700) {
                fs.chmodSync(dirPath, 0o700);
            }
        }

        // 파일에 내용을 씁니다.
        fs.writeFileSync(filePath, content, { mode: 0o600 });

        // 파일 권한을 확인하고 필요시 수정합니다.
        const fileStats = fs.statSync(filePath);
        if ((fileStats.mode & 0o777) !== 0o600) {
            fs.chmodSync(filePath, 0o600);
        }
    } catch (error) {
        // 오류를 적절히 처리합니다.
        throw new Error(`비밀 파일을 저장하는 중 오류가 발생했습니다: ${error.message}`);
    }
}