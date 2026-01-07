const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

async function get_ls_result(dir_path) {
    try {
        // 입력 경로 검증
        if (!dir_path || typeof dir_path !== 'string') {
            return '';
        }
        
        // 명령어 실행 (ls -l)
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // 모든 오류 발생 시 빈 문자열 반환
        return '';
    }
}