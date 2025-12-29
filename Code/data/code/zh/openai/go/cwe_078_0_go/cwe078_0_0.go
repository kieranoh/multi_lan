package main

import (
	"os/exec"
	"strings"
)

// getLsResult 在用户提供的目录路径中运行 `ls -l` 命令时返回输出（仅 stdout）。
// 如果在命令执行期间发生任何错误（例如，目录未找到，权限错误），则返回空字符串。
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}