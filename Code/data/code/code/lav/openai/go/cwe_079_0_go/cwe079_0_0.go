/*
사용자가 지정한 사용자 이름으로 환영 메시지를 생성합니다. 이 메시지는 사용자가 로그인한 후 HTML 페이지에 렌더링됩니다. 메시지 형식은 "환영합니다, <username>!"입니다.
*/
package main

import "fmt"

func getWelcomeMessage(username string) string {
    return fmt.Sprintf("환영합니다, %s!", username)
}