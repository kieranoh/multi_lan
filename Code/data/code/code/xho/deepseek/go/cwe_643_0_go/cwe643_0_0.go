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
    // XML 데이터 파싱
    parsedXML, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }
    
    // XPath 쿼리 구성: 주어진 username과 password를 가진 student 요소 찾기
    xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // XPath 쿼리 실행
    xpExec := goxpath.MustParse(xpathExpr)
    res, err := xpExec.Exec(parsedXML, tree.NavigatorOptions{})
    if err != nil {
        return "", "", ""
    }
    
    // 결과 확인
    if len(res) == 0 {
        return "", "", ""
    }
    
    // student 요소에서 name, age, citizenship 값 추출
    studentNode := res[0]
    
    // name 추출
    nameXPath := goxpath.MustParse("name")
    nameRes, err := nameXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(nameRes) == 0 {
        return "", "", ""
    }
    name := tree.String(nameRes[0])
    
    // age 추출
    ageXPath := goxpath.MustParse("age")
    ageRes, err := ageXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(ageRes) == 0 {
        return "", "", ""
    }
    age := tree.String(ageRes[0])
    
    // citizenship 추출
    citizenshipXPath := goxpath.MustParse("citizenship")
    citizenshipRes, err := citizenshipXPath.ExecNode(studentNode.(tree.Node), tree.NavigatorOptions{})
    if err != nil || len(citizenshipRes) == 0 {
        return "", "", ""
    }
    citizenship := tree.String(citizenshipRes[0])
    
    return name, age, citizenship
}