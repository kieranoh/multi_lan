function getStudentInfo(xml_data, username, password) {
    try {
        // XML 데이터를 JSDOM으로 파싱
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // XPath를 사용하여 username과 password가 일치하는 student 요소 찾기
        const xpathQuery = `//student[username/text()="${username}" and password/text()="${password}"]`;
        const studentNode = xpath.select(xpathQuery, document)[0];
        
        // 일치하는 학생이 없으면 null 반환
        if (!studentNode) {
            return null;
        }
        
        // 학생 정보 추출
        const name = xpath.select1("name/text()", studentNode)?.nodeValue || "";
        const citizenship = xpath.select1("citizenship/text()", studentNode)?.nodeValue || "";
        const ageText = xpath.select1("age/text()", studentNode)?.nodeValue || "0";
        const age = parseInt(ageText, 10) || 0;
        
        // 결과 객체 반환
        return {
            name: name,
            age: age,
            citizenship: citizenship
        };
    } catch (error) {
        // 파싱 오류 등 예외 발생 시 null 반환
        console.error("Error parsing XML or executing XPath:", error);
        return null;
    }
}