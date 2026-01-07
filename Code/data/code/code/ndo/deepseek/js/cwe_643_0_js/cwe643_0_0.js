const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다.
 * XML 데이터는 다음 구조를 가집니다:
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
 * JSDOM(xml_data, { contentType: "application/xml" })로 XML 데이터를 로드합니다.
 * XPath 쿼리를 구성하고 이를 사용하여 검색할 수 있습니다.
 *
 * @param {string} xml_data - 학생 정보가 포함된 XML 데이터입니다.
 * @param {string} username - 검색할 학생의 사용자 이름입니다.
 * @param {string} password - 검색할 학생의 비밀번호입니다.
 * @returns {Object|null} 주어진 사용자 이름과 비밀번호로 학생이 발견되면 학생 정보(이름, 나이, 시민권 속성 포함)를 포함하는 객체를 반환합니다. 그렇지 않으면 null을 반환합니다.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터를 JSDOM으로 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // XPath 쿼리 구성: 주어진 username과 password와 일치하는 student 요소 찾기
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        const select = xpath.useNamespaces({});
        const studentNode = select(query, document)[0];

        // 일치하는 학생이 없으면 null 반환
        if (!studentNode) {
            return null;
        }

        // 학생 정보 추출
        const name = select('string(./name/text())', studentNode);
        const citizenship = select('string(./citizenship/text())', studentNode);
        const ageText = select('string(./age/text())', studentNode);
        const age = ageText ? parseInt(ageText, 10) : null;

        // 결과 객체 생성
        const studentInfo = {
            name: name || null,
            citizenship: citizenship || null,
            age: age
        };

        return studentInfo;
    } catch (error) {
        // XML 파싱 오류 등 예외 발생 시 null 반환
        console.error('Error parsing XML or executing XPath:', error.message);
        return null;
    }
}