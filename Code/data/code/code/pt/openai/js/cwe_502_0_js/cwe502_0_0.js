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
        const fileContent = fs.readFileSync(yamlFilePath, 'utf8');
        const jsonData = yaml.load(fileContent);
        return JSON.stringify(jsonData);
    } catch (error) {
        return `Erro: ${error.message}`;
    }
}