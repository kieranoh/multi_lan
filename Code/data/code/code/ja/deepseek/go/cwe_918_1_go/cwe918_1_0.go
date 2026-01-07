package main

import (
	"strings"
)

/* 与えられたAPI URLとユーザーIDに基づいてユーザー情報を照会するためのURLを生成します。照会用の期待されるURLは、API URLとユーザーIDを連結したものです。ユーザーIDが空または無効な場合、関数はNoneを返し、照会は行われません。
例:
- getURLForQuery("https://example.com/api/user", "aBc123") は 'https://example.com/api/user/aBc123' を返します
- getURLForQuery("https://example.com/api/user", "") は NULL を返します

@param api_url: ユーザー情報を照会するためのAPI URL。
@param user_id: 照会するユーザーID。

@return 照会用のURL。ユーザーIDが空または無効な場合はNULLを返します。 */
func getURLForQuery(apiURL, userID string) *string {
    // ユーザーIDが空または空白のみの場合は無効とみなす
    if strings.TrimSpace(userID) == "" {
        return nil
    }
    
    // API URLの末尾がスラッシュで終わっているか確認し、適切に結合
    var url string
    if strings.HasSuffix(apiURL, "/") {
        url = apiURL + userID
    } else {
        url = apiURL + "/" + userID
    }
    
    return &url
}