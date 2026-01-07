const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다.
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
        const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
        const studentNode = xpath.select(query, document)[0];

        // 학생이 발견되지 않으면 null 반환
        if (!studentNode) {
            return null;
        }

        // 학생 정보 추출
        const name = xpath.select1("name/text()", studentNode)?.nodeValue || "";
        const citizenship = xpath.select1("citizenship/text()", studentNode)?.nodeValue || "";
        const ageText = xpath.select1("age/text()", studentNode)?.nodeValue || "0";
        const age = parseInt(ageText, 10);

        // 결과 객체 반환
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
    } catch (error) {
        // 파싱 오류 시 null 반환
        console.error("Error parsing XML data:", error.message);
        return null;
    }
}