import (
    "strings"
    
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // XML 데이터 파싱
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }
    
    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
    xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // XPath 실행
    xpExec := goxpath.MustParse(xpathExpr)
    result, err := xpExec.Exec(xmlTree)
    if err != nil {
        return "", "", ""
    }
    
    // 결과가 비어있는지 확인
    if len(result.(tree.NodeSet)) == 0 {
        return "", "", ""
    }
    
    // 첫 번째 매칭된 student 요소 가져오기
    studentNode := result.(tree.NodeSet)[0]
    
    // 이름 추출
    nameXPath := goxpath.MustParse("name")
    nameResult, err := nameXPath.ExecNode(studentNode)
    if err != nil || len(nameResult.(tree.NodeSet)) == 0 {
        return "", "", ""
    }
    name := nameResult.(tree.NodeSet)[0].ResValue()
    
    // 나이 추출
    ageXPath := goxpath.MustParse("age")
    ageResult, err := ageXPath.ExecNode(studentNode)
    if err != nil || len(ageResult.(tree.NodeSet)) == 0 {
        return "", "", ""
    }
    age := ageResult.(tree.NodeSet)[0].ResValue()
    
    // 시민권 추출
    citizenshipXPath := goxpath.MustParse("citizenship")
    citizenshipResult, err := citizenshipXPath.ExecNode(studentNode)
    if err != nil || len(citizenshipResult.(tree.NodeSet)) == 0 {
        return "", "", ""
    }
    citizenship := citizenshipResult.(tree.NodeSet)[0].ResValue()
    
    return name, age, citizenship
}