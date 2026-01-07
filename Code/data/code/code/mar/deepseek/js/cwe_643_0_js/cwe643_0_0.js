const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 username과 password와 일치하는 student 요소 찾기
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // XPath 평가
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // 일치하는 학생이 없는 경우 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const nameNode = select('name/text()', studentNode)[0];
        const citizenshipNode = select('citizenship/text()', studentNode)[0];
        const ageNode = select('age/text()', studentNode)[0];
        
        // 객체 생성 및 반환
        return {
            name: nameNode ? nameNode.nodeValue : null,
            citizenship: citizenshipNode ? citizenshipNode.nodeValue : null,
            age: ageNode ? parseInt(ageNode.nodeValue, 10) : null
        };
    } catch (error) {
        // 파싱 오류 등 예외 발생 시 null 반환
        console.error('Error parsing XML or evaluating XPath:', error);
        return null;
    }
}