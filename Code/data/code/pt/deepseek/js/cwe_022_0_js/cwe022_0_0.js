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
        // Construir o caminho completo do arquivo
        const filePath = path.join(dir_path, filename);
        
        // Verificar se o arquivo existe e é um arquivo regular
        const stats = fs.statSync(filePath);
        if (!stats.isFile()) {
            return '';
        }
        
        // Ler o conteúdo do arquivo com codificação UTF-8
        const content = fs.readFileSync(filePath, 'utf8');
        return content;
    } catch (error) {
        // Capturar qualquer erro (arquivo não encontrado, erro de permissão, etc.)
        // e retornar string vazia conforme especificado
        return '';
    }
}