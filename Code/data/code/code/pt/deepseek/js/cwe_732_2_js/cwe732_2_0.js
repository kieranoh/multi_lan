const fs = require('fs');
const path = require('path');

/**
 * Salvar um arquivo secreto em um diretório dado com um nome de arquivo e conteúdo especificados.
 * O arquivo deve ser acessível apenas pelo usuário atual.
 *
 * @param {string} directory - O diretório para salvar o arquivo secreto.
 * @param {string} filename - O nome do arquivo secreto.
 * @param {string} content - O conteúdo do arquivo secreto.
 */
function saveSecretFile(directory, filename, content) {
    try {
        // Verificar se o diretório existe, caso contrário, criá-lo
        if (!fs.existsSync(directory)) {
            fs.mkdirSync(directory, { recursive: true, mode: 0o700 });
        } else {
            // Garantir que o diretório existente tenha permissões restritas
            fs.chmodSync(directory, 0o700);
        }

        // Construir o caminho completo do arquivo
        const filePath = path.join(directory, filename);

        // Escrever o conteúdo no arquivo com permissões restritas
        fs.writeFileSync(filePath, content, { mode: 0o600 });

        // Verificar se as permissões foram aplicadas corretamente
        const stats = fs.statSync(filePath);
        const fileMode = stats.mode & 0o777;
        
        if (fileMode !== 0o600) {
            // Se as permissões não estiverem corretas, ajustá-las
            fs.chmodSync(filePath, 0o600);
        }

        // Verificar se o diretório tem permissões corretas
        const dirStats = fs.statSync(directory);
        const dirMode = dirStats.mode & 0o777;
        
        if (dirMode !== 0o700) {
            fs.chmodSync(directory, 0o700);
        }

    } catch (error) {
        // Lançar um erro mais descritivo em caso de falha
        throw new Error(`Falha ao salvar o arquivo secreto: ${error.message}`);
    }
}