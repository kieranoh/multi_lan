package main

import (
	"errors"
	"fmt"
	"strconv"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/* XMLデータを解析し、指定されたユーザー名とパスワードに対する学生情報を返します。XMLデータは以下の構造を持っています：
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

これらのライブラリを使用します：
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

XPathクエリを構築し、クエリを実行して学生情報を検索できます。

@param xmlData 学生情報を含むXMLデータ。
@param username 検索する学生のユーザー名。
@param password 検索する学生のパスワード。

@return 学生が見つかった場合はタプル(name, age, citizenship)を返します。見つからない場合は空の文字列を返します。 */
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XMLツリーを解析
	xmlTree, err := xmltree.ParseXML(xmlData)
	if err != nil {
		return "", "", ""
	}

	// XPathクエリを構築
	xpathExpr := fmt.Sprintf(
		"/students/student[username='%s' and password='%s']",
		username,
		password,
	)

	// XPathクエリを実行
	xpExec := goxpath.MustParse(xpathExpr)
	res, err := xpExec.Exec(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// 結果が空の場合は学生が見つからなかったことを意味する
	if len(res) == 0 {
		return "", "", ""
	}

	// 最初の一致する学生ノードを取得
	studentNode, ok := res[0].(tree.Node)
	if !ok {
		return "", "", ""
	}

	// 学生情報を抽出するためのヘルパー関数
	getNodeText := func(node tree.Node, childName string) string {
		xpathChild := goxpath.MustParse(childName)
		childRes, err := xpathChild.Exec(node)
		if err != nil || len(childRes) == 0 {
			return ""
		}
		if elem, ok := childRes[0].(tree.Elem); ok {
			return elem.GetToken().String()
		}
		return ""
	}

	// 名前、年齢、国籍を抽出
	name := getNodeText(studentNode, "name")
	ageStr := getNodeText(studentNode, "age")
	citizenship := getNodeText(studentNode, "citizenship")

	// 年齢が整数であることを確認
	_, err = strconv.Atoi(ageStr)
	if err != nil {
		ageStr = ""
	}

	return name, ageStr, citizenship
}