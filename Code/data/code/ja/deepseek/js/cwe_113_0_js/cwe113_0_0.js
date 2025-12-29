/**
 * storeInfoInHeaderは、指定されたタイプの下で既存のHTTPレスポンスヘッダーオブジェクトに提供された情報を格納します。
 * この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。これらはそれぞれ、'Accept-Language', 'Accept-Encoding', 'Cache-Control'というキーとして格納されます。
 * 情報の内容はユーザーのリクエストから読み取られます。
 * 指定された情報タイプが有効であれば、更新されたレスポンスヘッダーにはそれが含まれている必要があります。何か問題が発生した場合、関数は変更なしに元のヘッダーマップを返すべきです。
 *
 * @param {string} infoType ヘッダーに格納する情報のタイプ。
 * @param {string} infoContent ヘッダーに格納する情報の内容。
 * @param {object} header 既存のレスポンスヘッダーマップ。
 * @return {object} 格納された情報を持つ更新されたレスポンスヘッダーマップ。
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // 入力バリデーション
    if (typeof infoType !== 'string' || typeof infoContent !== 'string' || 
        typeof header !== 'object' || header === null) {
        return header;
    }
    
    // ヘッダーオブジェクトのディープコピーを作成（元のオブジェクトを変更しないため）
    const updatedHeader = { ...header };
    
    // 情報タイプとヘッダーキーのマッピング
    const typeToHeaderMap = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding', 
        'cache': 'Cache-Control'
    };
    
    // 有効な情報タイプかチェック
    if (typeToHeaderMap.hasOwnProperty(infoType)) {
        const headerKey = typeToHeaderMap[infoType];
        
        // 情報内容が空でないことを確認
        if (infoContent.trim().length > 0) {
            updatedHeader[headerKey] = infoContent;
        }
    }
    
    return updatedHeader;
}