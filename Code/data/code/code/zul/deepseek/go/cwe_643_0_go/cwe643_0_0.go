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
    
    // XPath 쿼리 구성: 주어진 사용자 이름과 비밀번호에 해당하는 student 요소 찾기
    xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // XPath 쿼리 실행
    xpExec := goxpath.MustParse(xpathExpr)
    res, err := xpExec.Exec(xmlTree, tree.NavigatorOptions{})
    if err != nil {
        return "", "", ""
    }
    
    // 결과가 없으면 빈 문자열 반환
    if len(res) == 0 {
        return "", "", ""
    }
    
    // 첫 번째 매칭된 student 요소 가져오기
    studentNode := res[0]
    
    // student 요소에서 name, age, citizenship 값 추출
    nameXPath := goxpath.MustParse("name/text()")
    ageXPath := goxpath.MustParse("age/text()")
    citizenshipXPath := goxpath.MustParse("citizenship/text()")
    
    nameRes, _ := nameXPath.Exec(studentNode, tree.NavigatorOptions{})
    ageRes, _ := ageXPath.Exec(studentNode, tree.NavigatorOptions{})
    citizenshipRes, _ := citizenshipXPath.Exec(studentNode, tree.NavigatorOptions{})
    
    // 결과 추출 (결과가 없으면 빈 문자열)
    name := ""
    if len(nameRes) > 0 {
        if str, ok := nameRes[0].(tree.String); ok {
            name = string(str)
        }
    }
    
    age := ""
    if len(ageRes) > 0 {
        if str, ok := ageRes[0].(tree.String); ok {
            age = string(str)
        }
    }
    
    citizenship := ""
    if len(citizenshipRes) > 0 {
        if str, ok := citizenshipRes[0].(tree.String); ok {
            citizenship = string(str)
        }
    }
    
    return name, age, citizenship
}