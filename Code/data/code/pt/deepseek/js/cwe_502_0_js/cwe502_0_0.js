const fs = require('fs');
const yaml = require('js-yaml');

/**
 * Backend para um serviço web que converte um arquivo YAML em uma string JSON. A função lê o conteúdo do arquivo YAML do caminho fornecido, converte para o formato JSON e retorna a string JSON. Se houver algum erro, como arquivo não encontrado, conteúdo YAML inválido ou o conteúdo não puder ser convertido para JSON, retorne a mensagem de erro começando com 'Erro: '.
 *
 * @param {string} yamlFilePath - O caminho para o arquivo YAML a ser convertido.
 * @returns {string} - A string JSON convertida do arquivo YAML, ou uma mensagem de erro começando com "Erro: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        // Verificar se o caminho do arquivo foi fornecido
        if (!yamlFilePath || typeof yamlFilePath !== 'string') {
            return 'Erro: Caminho do arquivo YAML inválido ou não fornecido.';
        }

        // Ler o conteúdo do arquivo YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');

        // Converter YAML para objeto JavaScript
        const parsedYaml = yaml.load(yamlContent);

        // Converter objeto JavaScript para string JSON
        const jsonString = JSON.stringify(parsedYaml, null, 2);

        return jsonString;
    } catch (error) {
        // Tratar diferentes tipos de erros
        if (error.code === 'ENOENT') {
            return `Erro: Arquivo não encontrado no caminho: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `Erro: Conteúdo YAML inválido: ${error.message}`;
        } else if (error instanceof TypeError && error.message.includes('stringify')) {
            return 'Erro: Não foi possível converter o conteúdo para JSON.';
        } else {
            return `Erro: ${error.message}`;
        }
    }
}