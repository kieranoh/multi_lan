import (
    "strings"
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // XML 데이터 파싱
    xTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }
    
    // XPath 쿼리 구성 - 주어진 사용자 이름과 비밀번호에 해당하는 student 요소 찾기
    xPathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // XPath 실행
    xpExec := goxpath.MustParse(xPathExpr)
    res, err := xpExec.Exec(xTree, tree.NsMap{})
    if err != nil {
        return "", "", ""
    }
    
    // 결과가 비어있는지 확인
    if len(res) == 0 {
        return "", "", ""
    }
    
    // 첫 번째 일치하는 student 요소 가져오기
    studentNode := res[0]
    
    // student 요소에서 필요한 정보 추출
    namePath := goxpath.MustParse("name")
    citizenshipPath := goxpath.MustParse("citizenship")
    agePath := goxpath.MustParse("age")
    
    nameRes, _ := namePath.Exec(studentNode.(tree.Node), tree.NsMap{})
    citizenshipRes, _ := citizenshipPath.Exec(studentNode.(tree.Node), tree.NsMap{})
    ageRes, _ := agePath.Exec(studentNode.(tree.Node), tree.NsMap{})
    
    // 결과 추출 및 반환
    name := ""
    citizenship := ""
    age := ""
    
    if len(nameRes) > 0 {
        if n, ok := nameRes[0].(tree.Elem); ok {
            name = string(n.NodeValue())
        }
    }
    
    if len(citizenshipRes) > 0 {
        if c, ok := citizenshipRes[0].(tree.Elem); ok {
            citizenship = string(c.NodeValue())
        }
    }
    
    if len(ageRes) > 0 {
        if a, ok := ageRes[0].(tree.Elem); ok {
            age = string(a.NodeValue())
        }
    }
    
    return name, age, citizenship
}