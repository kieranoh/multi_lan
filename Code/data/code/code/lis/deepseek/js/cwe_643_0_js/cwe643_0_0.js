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

        // XPath 쿼리를 구성하여 주어진 사용자 이름과 비밀번호에 해당하는 student 요소를 찾음
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        const studentNode = xpath.select(query, document);

        // 학생이 발견되지 않은 경우 null 반환
        if (!studentNode || studentNode.length === 0) {
            return null;
        }

        // 첫 번째 일치하는 student 요소를 가져옴
        const student = studentNode[0];

        // 필요한 정보를 추출
        const nameNode = xpath.select1("name", student);
        const citizenshipNode = xpath.select1("citizenship", student);
        const ageNode = xpath.select1("age", student);

        // 정보가 모두 존재하는지 확인
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }

        // 객체로 반환
        return {
            name: nameNode.textContent,
            citizenship: citizenshipNode.textContent,
            age: parseInt(ageNode.textContent, 10)
        };
    } catch (error) {
        // 파싱 오류 또는 기타 예외 발생 시 null 반환
        console.error("Error parsing XML or executing XPath query:", error);
        return null;
    }
}