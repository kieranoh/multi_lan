package main

import (
	"fmt"
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo phân tích dữ liệu XML và trả về thông tin sinh viên cho tên người dùng và mật khẩu đã cho.
// @param xmlData Dữ liệu XML chứa thông tin sinh viên.
// @param username Tên người dùng của sinh viên cần tìm.
// @param password Mật khẩu của sinh viên cần tìm.
// @return Một tuple (name, age, citizenship) nếu sinh viên được tìm thấy. Ngược lại, trả về chuỗi rỗng.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	doc, err := xmltree.ParseString(xmlData)
	if err != nil {
		return "", "", ""
	}

	query := fmt.Sprintf("//student[username='%s' and password='%s']", username, password)
	nodes, err := goxpath.Eval(query, doc)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	studentNode := nodes[0]

	name := studentNode.Select("name").Text()
	age := studentNode.Select("age").Text()
	citizenship := studentNode.Select("citizenship").Text()

	return name, age, citizenship
}