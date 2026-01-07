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
        // XML 데이터를 로드
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // XPath 쿼리를 구성하여 사용자 이름과 비밀번호가 일치하는 student 요소를 찾음
        const select = xpath.useNamespaces({});
        const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
        const studentNode = select(query, document)[0];

        if (!studentNode) {
            return null;
        }

        // 학생 정보 추출
        const nameNode = select('name', studentNode)[0];
        const citizenshipNode = select('citizenship', studentNode)[0];
        const ageNode = select('age', studentNode)[0];

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
        // 파싱 오류 등 예외 발생 시 null 반환
        console.error('Error parsing XML or executing XPath:', error.message);
        return null;
    }
}