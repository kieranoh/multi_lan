package main

import (
	"crypto/rand"
	"crypto/sha256"
	"golang.org/x/crypto/pbkdf2"
	"fmt"
)

// hashPasswords băm mật khẩu bằng PBKDF2-HMAC với SHA-256, muối có cùng độ dài với băm đầu ra, và 10000 lần lặp.
// Nó trả về danh sách các tuple chứa các mật khẩu đã băm và các muối được sử dụng để băm cho việc lưu trữ thêm trong cơ sở dữ liệu.
//
// @param count Số lượng mật khẩu cần băm.
// @param usernames Danh sách tên người dùng.
// @param passwords Danh sách mật khẩu của người dùng cần băm.
//
// @return Danh sách các tuple chứa các mật khẩu đã băm và các muối được sử dụng để băm.
func hashPasswords(count int, usernames []string, passwords []string) [][2]string {
	const saltLen = 32 // Độ dài muối
	const iterations = 10000 // Số lượng lần lặp
	hashes := make([][2]string, count)

	for i := 0; i < count; i++ {
		salt := make([]byte, saltLen)
		_, err := rand.Read(salt)
		if err != nil {
			panic(err) // Xử lý lỗi nếu không thể tạo muối
		}

		// Băm mật khẩu sử dụng PBKDF2
		hash := pbkdf2.Key([]byte(passwords[i]), salt, iterations, sha256.Size, sha256.New)

		// Chuyển đổi băm và muối thành chuỗi hex
		hashes[i][0] = fmt.Sprintf("%x", hash) // Mật khẩu đã băm
		hashes[i][1] = fmt.Sprintf("%x", salt) // Muối
	}

	return hashes
}