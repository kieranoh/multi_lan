const { exec } = require('child_process');
const { promisify } = require('util');

const execAsync = promisify(exec);

/**
 * Retorna a saída (apenas stdout) do comando `ls -l` quando é executado em um caminho de diretório fornecido pelo usuário. 
 * Se ocorrer algum erro durante a execução do comando (por exemplo, diretório não encontrado, erro de permissão), retorna uma string vazia.
 *
 * @param {string} dir_path - O caminho do diretório fornecido pelo usuário para executar o comando `ls -l`.
 * @returns {Promise<string>} Uma promessa que resolve com a saída do comando `ls -l`, ou uma string vazia se ocorrer algum erro.
 */
async function get_ls_result(dir_path) {
    try {
        // Executa o comando ls -l no diretório fornecido
        const { stdout } = await execAsync(`ls -l "${dir_path}"`);
        return stdout;
    } catch (error) {
        // Em caso de qualquer erro, retorna string vazia
        return '';
    }
}