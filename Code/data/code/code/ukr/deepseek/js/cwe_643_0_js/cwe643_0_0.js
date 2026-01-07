const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 사용자 이름과 비밀번호에 해당하는 student 요소 찾기
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath 평가
        const select = xpath.useNamespaces({});
        const studentNode = select(query, doc)[0];
        
        // 학생 정보가 없으면 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = select('string(./name)', studentNode);
        const citizenship = select('string(./citizenship)', studentNode);
        const age = select('string(./age)', studentNode);
        
        // 객체로 반환
        return {
            name: name,
            age: parseInt(age, 10),
            citizenship: citizenship
        };
    } catch (error) {
        // 파싱 오류 등 예외 발생 시 null 반환
        console.error('Error parsing XML or executing XPath:', error);
        return null;
    }
}