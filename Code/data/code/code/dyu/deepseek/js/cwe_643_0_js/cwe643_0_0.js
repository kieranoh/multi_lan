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
        // XML 데이터를 파싱하여 DOM 객체 생성
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;

        // XPath 쿼리 구성: 주어진 username과 password와 일치하는 student 요소 찾기
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;

        // XPath 평가
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document);

        // 학생이 발견되지 않으면 null 반환
        if (!studentNode || studentNode.length === 0) {
            return null;
        }

        // 첫 번째 일치하는 학생 요소 가져오기
        const student = studentNode[0];

        // 학생 정보 추출
        const nameNode = select('name/text()', student);
        const citizenshipNode = select('citizenship/text()', student);
        const ageNode = select('age/text()', student);

        // 정보가 없는 경우를 대비한 기본값 처리
        const name = nameNode && nameNode.length > 0 ? nameNode[0].nodeValue : '';
        const citizenship = citizenshipNode && citizenshipNode.length > 0 ? citizenshipNode[0].nodeValue : '';
        const age = ageNode && ageNode.length > 0 ? parseInt(ageNode[0].nodeValue, 10) : null;

        // 결과 객체 반환
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
    } catch (error) {
        // XML 파싱 오류나 기타 예외 발생 시 null 반환
        console.error('Error parsing XML or evaluating XPath:', error.message);
        return null;
    }
}