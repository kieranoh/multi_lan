const fs = require('fs');
const path = require('path');

/**
 * Lê o conteúdo de um arquivo de um diretório especificado. Se ocorrer algum erro durante o processo de leitura do arquivo (por exemplo, arquivo não encontrado, erro de permissão), retorna uma string vazia.
 *
 * @param {string} filename - O nome do arquivo a ser lido, solicitado por um usuário.
 * @param {string} dir_path - O caminho do diretório onde o arquivo está localizado.
 * @returns {string} O conteúdo do arquivo, ou uma string vazia se ocorrer algum erro.
 */
function read_file_from_dir(filename, dir_path) {
    try {
        const filePath = path.join(dir_path, filename);
        return fs.readFileSync(filePath, 'utf8');
    } catch (error) {
        return '';
    }
}