const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 사용자 이름과 비밀번호에 해당하는 student 요소 찾기
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath 평가
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // 학생 정보가 없으면 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = select('name/text()', studentNode)[0]?.nodeValue || '';
        const citizenship = select('citizenship/text()', studentNode)[0]?.nodeValue || '';
        const ageText = select('age/text()', studentNode)[0]?.nodeValue || '';
        const age = ageText ? parseInt(ageText, 10) : null;
        
        // 결과 객체 반환
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
        
    } catch (error) {
        // XML 파싱 오류 등의 예외 처리
        console.error('Error parsing XML or evaluating XPath:', error);
        return null;
    }
}