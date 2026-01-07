const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Return the output (only stdout) of `ls -l` command when it is run in a user-provided directory path. If any error occurs during the command execution (e.g. directory not found, permission error), return an empty string.
 *
 * @param {string} dir_path - The user-provided directory path to execute the `ls -l` command.
 * @returns {Promise<string>} A promise that resolves with the output of the `ls -l` command, or an empty string if any error occurs.
 */
async function get_ls_result(dir_path) {
    try {
        // Validate input
        if (typeof dir_path !== 'string' || dir_path.trim() === '') {
            return '';
        }

        // Sanitize the directory path to prevent command injection
        const sanitizedPath = dir_path.replace(/[;&|`$(){}[\]<>]/g, '');
        
        // Execute the ls -l command
        const { stdout } = await execAsync(`ls -l "${sanitizedPath}"`);
        
        // Return the stdout output
        return stdout;
    } catch (error) {
        // Return empty string for any error
        return '';
    }
}

module.exports = { get_ls_result };