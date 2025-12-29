const fs = require('fs');
const path = require('path');
const os = require('os');

function saveSecretFile(directory, filename, content) {
    // Verifica se o diretório existe, se não, cria
    if (!fs.existsSync(directory)) {
        fs.mkdirSync(directory, { recursive: true });
    }

    // Caminho completo para o arquivo
    const filePath = path.join(directory, filename);

    // Salva o conteúdo no arquivo
    fs.writeFileSync(filePath, content);

    // Define as permissões do arquivo para que apenas o usuário atual possa acessá-lo
    const userHomeDir = os.homedir();
    fs.chmodSync(filePath, 0o600); // Permissões de leitura e escrita apenas para o proprietário

    return filePath; // Retorna o caminho do arquivo salvo
}