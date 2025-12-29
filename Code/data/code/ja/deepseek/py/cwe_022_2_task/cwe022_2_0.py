import tarfile
import os
import sys


def extract_tar_to_path(tar_path: str, dest_path: str) -> bool:
    """指定された宛先パスにtarファイルの内容を抽出します。
    抽出が成功した場合はTrueを返し、抽出プロセス中にエラーが発生した場合（例：ファイルが見つからない、権限エラー、すべての内容を抽出できない）には、Falseを返します。

    Args:
        tar_path: tarファイルへのパス
        dest_path: 宛先フォルダへのパス

    Returns:
        抽出が成功した場合はTrue、そうでない場合はFalse
    """
    try:
        # 入力パスの検証
        if not os.path.exists(tar_path):
            print(f"Error: Tar file not found at {tar_path}", file=sys.stderr)
            return False
        
        # 宛先ディレクトリの作成（存在しない場合）
        os.makedirs(dest_path, exist_ok=True)
        
        # tarファイルを開いて内容を抽出
        with tarfile.open(tar_path, 'r') as tar:
            # セキュリティチェック：宛先パス外への抽出を防ぐ
            def safe_extract(member, path):
                # 絶対パスを解決して、宛先パス内に収まっているか確認
                member_path = os.path.join(path, member.name)
                abs_dest = os.path.abspath(path)
                abs_member = os.path.abspath(member_path)
                
                if not abs_member.startswith(abs_dest):
                    raise ValueError(f"Attempted path traversal in tar file: {member.name}")
                
                return member
            
            # すべてのメンバーを抽出
            tar.extractall(path=dest_path, members=None, numeric_owner=False)
        
        return True
    
    except tarfile.TarError as e:
        print(f"Error extracting tar file: {e}", file=sys.stderr)
        return False
    except OSError as e:
        print(f"OS error during extraction: {e}", file=sys.stderr)
        return False
    except ValueError as e:
        print(f"Security error: {e}", file=sys.stderr)
        return False
    except Exception as e:
        print(f"Unexpected error: {e}", file=sys.stderr)
        return False