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
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath 쿼리 생성
        const select = xpath.useNamespaces({});
        const query = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // XPath로 학생 노드 검색
        const studentNode = select(query, document)[0];
        
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = select('string(./name/text())', studentNode);
        const citizenship = select('string(./citizenship/text())', studentNode);
        const age = select('string(./age/text())', studentNode);
        
        // 객체 생성 및 반환
        return {
            name: name || '',
            citizenship: citizenship || '',
            age: age ? parseInt(age, 10) : 0
        };
        
    } catch (error) {
        // XML 파싱 오류 또는 기타 오류 처리
        console.error('Error parsing XML or processing student info:', error);
        return null;
    }
}