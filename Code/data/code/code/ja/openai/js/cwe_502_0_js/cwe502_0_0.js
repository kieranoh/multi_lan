const fs = require('fs');
const yaml = require('js-yaml');

/**
 * YAMLファイルをJSON文字列に変換するウェブサービスのバックエンド。関数は指定されたパスからYAMLファイルの内容を読み込み、それをJSON形式に変換してJSON文字列を返します。ファイルが見つからない、無効なYAML内容、または内容がJSONに変換できないなどのエラーが発生した場合は、'Error: 'で始まるエラーメッセージを返します。
 *
 * @param {string} yamlFilePath - 変換するYAMLファイルへのパス。
 * @returns {string} - YAMLファイルから変換されたJSON文字列、または"Error: "で始まるエラーメッセージ。
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (e) {
        return 'Error: ' + e.message;
    }
}