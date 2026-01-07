const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * 사용자가 제공한 디렉토리 경로에서 실행될 때 `ls -l` 명령의 출력(오직 stdout)을 반환합니다.
 * 명령 실행 중 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.
 * 
 * @param {string} dir_path - `ls -l` 명령을 실행할 사용자 제공 디렉토리 경로입니다.
 * @returns {Promise<string>} `ls -l` 명령의 출력으로 해결되는 프로미스, 또는 오류가 발생하면 빈 문자열입니다.
 */
async function get_ls_result(dir_path) {
    try {
        // 입력 유효성 검사
        if (!dir_path || typeof dir_path !== 'string') {
            return '';
        }

        // 경로에 공백이 포함된 경우 따옴표로 감싸기
        const sanitizedPath = dir_path.replace(/"/g, '\\"');
        const command = `ls -l "${sanitizedPath}"`;

        const { stdout } = await execAsync(command, {
            cwd: process.cwd(),
            encoding: 'utf8',
            timeout: 5000 // 5초 타임아웃
        });

        // stdout에서 불필요한 공백 제거
        return stdout.trim();
    } catch (error) {
        // 모든 오류에 대해 빈 문자열 반환
        return '';
    }
}