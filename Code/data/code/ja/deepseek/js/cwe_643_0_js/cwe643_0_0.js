const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。XMLデータは以下の構造を持っています：
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>John Doe</name>
 *         <citizenship>USA</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>Bob Smith</name>
 *         <citizenship>Canada</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * JSDOM(xml_data, { contentType: "application/xml" })を使用してXMLデータを読み込みます。
 * XPathクエリを構築し、それを使用して検索できます。
 *
 * @param {string} xml_data - 学生情報を含むXMLデータ。
 * @param {string} username - 検索する学生のユーザー名。
 * @param {string} password - 検索する学生のパスワード。
 * @returns {Object|null} 指定されたユーザー名とパスワードで学生が見つかった場合、学生情報（name、age、citizenshipプロパティを含む）を持つオブジェクトを返します。そうでない場合はnullを返します。
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // XMLドキュメントをパース
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // XPathクエリを構築して、指定されたユーザー名とパスワードに一致する学生を検索
        const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
        const select = xpath.useNamespaces({});
        const studentNode = select(query, doc)[0];
        
        // 学生が見つからない場合はnullを返す
        if (!studentNode) {
            return null;
        }
        
        // 学生情報を抽出
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // 必要なプロパティがすべて存在することを確認
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // オブジェクトを構築して返す
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: parseInt(ageNode.nodeValue, 10)
        };
    } catch (error) {
        // パースエラーなどの例外が発生した場合はnullを返す
        console.error('Error parsing XML:', error);
        return null;
    }
}