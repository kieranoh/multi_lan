const { JSDOM } = require('jsdom');
const xpath = require('xpath');

function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 사용자 이름과 비밀번호에 해당하는 student 요소 찾기
        const xpathQuery = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // XPath 쿼리 실행
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // 학생 정보가 없으면 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const nameNode = select("name", studentNode)[0];
        const citizenshipNode = select("citizenship", studentNode)[0];
        const ageNode = select("age", studentNode)[0];
        
        // 객체 구성 및 반환
        return {
            name: nameNode ? nameNode.textContent : null,
            citizenship: citizenshipNode ? citizenshipNode.textContent : null,
            age: ageNode ? parseInt(ageNode.textContent, 10) : null
        };
    } catch (error) {
        // XML 파싱 오류 등 예외 처리
        console.error("Error parsing XML or executing XPath:", error);
        return null;
    }
}