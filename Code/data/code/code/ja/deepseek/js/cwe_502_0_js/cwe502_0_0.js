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
        // ファイルの読み込み
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // YAMLをJavaScriptオブジェクトにパース
        const parsedObject = yaml.load(yamlContent);
        
        // JavaScriptオブジェクトをJSON文字列に変換
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // エラーメッセージを生成
        let errorMessage = 'Error: ';
        
        if (error.code === 'ENOENT') {
            errorMessage += 'File not found';
        } else if (error instanceof yaml.YAMLException) {
            errorMessage += 'Invalid YAML content';
        } else if (error instanceof TypeError && error.message.includes('cyclic')) {
            errorMessage += 'Content cannot be converted to JSON (circular reference)';
        } else {
            errorMessage += error.message;
        }
        
        return errorMessage;
    }
}