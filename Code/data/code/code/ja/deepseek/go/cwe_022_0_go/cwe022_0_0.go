import (
	"io/ioutil"
	"os"
	"path/filepath"
)

/* ユーザーが提供したディレクトリパスとファイル名を指定して、ディレクトリからファイルを読み込み、その内容を返します。ファイル読み込みプロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー）、空の文字列を返します。返された文字列は呼び出し元によって解放されます。

@param filename 読み取るファイルの名前、ユーザーによって要求されます。
@param dir_path ファイルが存在するディレクトリのパス。

@return ファイルが存在し、アクセス可能な場合はその内容、そうでなければ空の文字列。 */
func readFileFromDir(filename, dirPath string) string {
	// パスを安全に結合
	filePath := filepath.Join(dirPath, filename)
	
	// ファイルの存在確認と読み込み
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		// エラーが発生した場合は空文字列を返す
		return ""
	}
	
	// バイトスライスを文字列に変換して返す
	return string(content)
}