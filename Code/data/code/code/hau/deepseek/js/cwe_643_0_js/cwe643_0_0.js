function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const doc = dom.window.document;
        
        // XPath 쿼리 구성: 주어진 username과 password에 해당하는 student 요소 찾기
        const xpathQuery = `//student[username/text()="${username}" and password/text()="${password}"]`;
        
        // XPath 평가
        const studentNode = xpath.select(xpathQuery, doc)[0];
        
        // 학생 정보가 없으면 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = xpath.select1("name/text()", studentNode)?.nodeValue || "";
        const citizenship = xpath.select1("citizenship/text()", studentNode)?.nodeValue || "";
        const ageText = xpath.select1("age/text()", studentNode)?.nodeValue || "";
        const age = ageText ? parseInt(ageText, 10) : null;
        
        // 결과 객체 반환
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
    } catch (error) {
        // 파싱 오류 등 예외 발생 시 null 반환
        console.error("Error parsing XML or evaluating XPath:", error);
        return null;
    }
}