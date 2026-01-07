const { exec } = require('child_process');

/**
 * Retorna a saída (apenas stdout) do comando `ls -l` quando é executado em um caminho de diretório fornecido pelo usuário. Se ocorrer algum erro durante a execução do comando (por exemplo, diretório não encontrado, erro de permissão), retorna uma string vazia.
 *
 * @param {string} dir_path - O caminho do diretório fornecido pelo usuário para executar o comando `ls -l`.
 * @returns {Promise<string>} Uma promessa que resolve com a saída do comando `ls -l`, ou uma string vazia se ocorrer algum erro.
 */
function get_ls_result(dir_path) {
    return new Promise((resolve) => {
        exec(`ls -l ${dir_path}`, (error, stdout, stderr) => {
            if (error || stderr) {
                resolve('');
            } else {
                resolve(stdout);
            }
        });
    });
}