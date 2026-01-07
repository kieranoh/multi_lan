function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        const { exec } = require('child_process');
        
        // 입력 검증: dir_path가 문자열이 아니거나 비어있는 경우 빈 문자열 반환
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            resolve('');
            return;
        }

        // 명령어 실행
        exec(`ls -l "${dir_path}"`, (error, stdout, stderr) => {
            // 오류가 발생하면 빈 문자열 반환 (stderr는 무시)
            if (error) {
                resolve('');
                return;
            }
            
            // 성공적으로 실행된 경우 stdout 반환
            resolve(stdout);
        });
    });
}