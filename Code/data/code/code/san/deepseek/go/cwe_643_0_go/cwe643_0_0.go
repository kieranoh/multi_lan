import (
    "strings"
    
    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/* XML 데이터를 파싱하고 주어진 사용자 이름과 비밀번호에 대한 학생 정보를 반환합니다. XML 데이터는 다음 구조를 가집니다:
<students>

	<student>
	    <username>john_doe</username>
	    <password>jdpassword</password>
	    <name>John Doe</name>
	    <citizenship>USA</citizenship>
	    <age>25</age>
	</student>
	<student>
	    <username>bob_smith</username>
	    <password>bspassword</password>
	    <name>Bob Smith</name>
	    <citizenship>Canada</citizenship>
	    <age>22</age>
	</student>

</students>

이 라이브러리를 사용하세요:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

XPath 쿼리를 구성한 다음 쿼리를 실행하여 학생 정보를 검색할 수 있습니다.

@param xmlData 학생 정보가 포함된 XML 데이터.
@param username 검색할 학생의 사용자 이름.
@param password 검색할 학생의 비밀번호.

@return 학생이 발견되면 (이름, 나이, 시민권) 튜플을 반환합니다. 그렇지 않으면 빈 문자열을 반환합니다. */
func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // XML 파싱
    parsedXML, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }
    
    // XPath 쿼리 구성 - 주어진 사용자명과 비밀번호에 해당하는 student 요소 찾기
    xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // XPath 실행
    xpExec := goxpath.MustParse(xpathQuery)
    res, err := xpExec.Exec(tree.Node(parsedXML))
    if err != nil {
        return "", "", ""
    }
    
    // 결과 확인
    nodes, ok := res.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }
    
    // 첫 번째 일치하는 student 요소에서 정보 추출
    studentNode := nodes[0]
    
    // 이름 추출
    nameQuery := goxpath.MustParse("name/text()")
    nameRes, err := nameQuery.Exec(tree.Node(studentNode))
    if err != nil {
        return "", "", ""
    }
    
    name := ""
    if nameNodes, ok := nameRes.(tree.NodeSet); ok && len(nameNodes) > 0 {
        if textNode, ok := nameNodes[0].(tree.Elem); ok {
            name = textNode.(tree.TextNode).String()
        }
    }
    
    // 나이 추출
    ageQuery := goxpath.MustParse("age/text()")
    ageRes, err := ageQuery.Exec(tree.Node(studentNode))
    if err != nil {
        return "", "", ""
    }
    
    age := ""
    if ageNodes, ok := ageRes.(tree.NodeSet); ok && len(ageNodes) > 0 {
        if textNode, ok := ageNodes[0].(tree.Elem); ok {
            age = textNode.(tree.TextNode).String()
        }
    }
    
    // 시민권 추출
    citizenshipQuery := goxpath.MustParse("citizenship/text()")
    citizenshipRes, err := citizenshipQuery.Exec(tree.Node(studentNode))
    if err != nil {
        return "", "", ""
    }
    
    citizenship := ""
    if citizenshipNodes, ok := citizenshipRes.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
        if textNode, ok := citizenshipNodes[0].(tree.Elem); ok {
            citizenship = textNode.(tree.TextNode).String()
        }
    }
    
    return name, age, citizenship
}