import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parseatu XML datua
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Eraiki XPath galdera erabiltzaile izena eta pasahitza bat datozen ikaslea bilatzeko
    xpathExpr := goxpath.MustParse(
        `/students/student[username/text() = $user and password/text() = $pass]`,
    )

    // Exekutatu XPath galdera
    result, err := xpathExpr.ExecNode(
        tree.Node(xmlTree),
        func(o *goxpath.Opts) {
            o.Vars["user"] = tree.String(username)
            o.Vars["pass"] = tree.String(password)
        },
    )
    if err != nil {
        return "", "", ""
    }

    // Emaitza hutsa bada, itzuli kate hutsak
    if len(result) == 0 {
        return "", "", ""
    }

    // Lehenengo emaitza hartu (bat baino gehiago ez dagoela suposatuz)
    studentNode := result[0]

    // Bilatu izena, adina eta herritartasuna ikaslearen nodoaren barruan
    nameExpr := goxpath.MustParse("name/text()")
    ageExpr := goxpath.MustParse("age/text()")
    citizenshipExpr := goxpath.MustParse("citizenship/text()")

    nameResult, err := nameExpr.ExecNode(tree.Node(studentNode))
    if err != nil || len(nameResult) == 0 {
        return "", "", ""
    }

    ageResult, err := ageExpr.ExecNode(tree.Node(studentNode))
    if err != nil || len(ageResult) == 0 {
        return "", "", ""
    }

    citizenshipResult, err := citizenshipExpr.ExecNode(tree.Node(studentNode))
    if err != nil || len(citizenshipResult) == 0 {
        return "", "", ""
    }

    // Itzuli balioak string moduan
    name := nameResult[0].ResValue()
    age := ageResult[0].ResValue()
    citizenship := citizenshipResult[0].ResValue()

    return name, age, citizenship
}