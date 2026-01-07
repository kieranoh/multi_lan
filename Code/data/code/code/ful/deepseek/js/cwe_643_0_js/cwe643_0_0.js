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
        // XML 문서 로드
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
        const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // XPath 평가
        const select = xpath.useNamespaces({});
        const studentNode = select(query, doc)[0];
        
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = select('string(./name)', studentNode);
        const citizenship = select('string(./citizenship)', studentNode);
        const ageText = select('string(./age)', studentNode);
        const age = ageText ? parseInt(ageText, 10) : null;
        
        // 결과 객체 반환
        return {
            name: name || null,
            citizenship: citizenship || null,
            age: isNaN(age) ? null : age
        };
    } catch (error) {
        // 파싱 오류나 기타 예외 발생 시 null 반환
        console.error('Error parsing XML or evaluating XPath:', error.message);
        return null;
    }
}