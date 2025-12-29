import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse XML data
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Create XPath expression to find student with matching username and password
    xpathExpr := goxpath.MustParse(
        `/students/student[username/text() = $username and password/text() = $password]`,
    )

    // Execute XPath query with parameters
    result, err := xpathExpr.Exec(
        xmlTree,
        tree.NsMap{},
        func(o *goxpath.Opts) {
            o.Vars["username"] = tree.String(username)
            o.Vars["password"] = tree.String(password)
        },
    )
    if err != nil {
        return "", "", ""
    }

    // Check if we found a student
    nodes, ok := result.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }

    // Get the first matching student node
    studentNode := nodes[0]

    // Extract name, age, and citizenship using XPath
    nameExpr := goxpath.MustParse("name/text()")
    ageExpr := goxpath.MustParse("age/text()")
    citizenshipExpr := goxpath.MustParse("citizenship/text()")

    nameResult, err := nameExpr.ExecNode(studentNode)
    if err != nil {
        return "", "", ""
    }

    ageResult, err := ageExpr.ExecNode(studentNode)
    if err != nil {
        return "", "", ""
    }

    citizenshipResult, err := citizenshipExpr.ExecNode(studentNode)
    if err != nil {
        return "", "", ""
    }

    // Convert results to strings
    name := ""
    if nameNodes, ok := nameResult.(tree.NodeSet); ok && len(nameNodes) > 0 {
        if str, ok := nameNodes[0].(tree.String); ok {
            name = string(str)
        }
    }

    age := ""
    if ageNodes, ok := ageResult.(tree.NodeSet); ok && len(ageNodes) > 0 {
        if str, ok := ageNodes[0].(tree.String); ok {
            age = string(str)
        }
    }

    citizenship := ""
    if citizenshipNodes, ok := citizenshipResult.(tree.NodeSet); ok && len(citizenshipNodes) > 0 {
        if str, ok := citizenshipNodes[0].(tree.String); ok {
            citizenship = string(str)
        }
    }

    return name, age, citizenship
}