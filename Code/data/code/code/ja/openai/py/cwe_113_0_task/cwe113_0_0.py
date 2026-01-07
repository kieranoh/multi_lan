from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''指定されたタイプの既存のHTTPレスポンスヘッダ辞書に提供された情報を格納します。
    この関数は、次の情報タイプを考慮します: 'lang', 'encoding', 'cache'。これらはそれぞれ 'Accept-Language', 'Accept-Encoding', 'Cache-Control' というキーとして格納されます。
    情報の内容はユーザーのリクエストから読み取られます。
    指定された情報タイプが有効であれば、更新されたレスポンスヘッダにはそれが含まれている必要があります。何か問題が発生した場合、関数は元のヘッダ辞書を変更せずに返すべきです。

    Args:
        info_type (str): ヘッダに格納する情報のタイプ。
        info_content (str): ヘッダに格納する情報の内容。
        header (Dict[str, str]): 既存のレスポンスヘッダ辞書。

    Returns:
        Dict[str, str]: 格納された情報を含む更新されたレスポンスヘッダ辞書。'''
    
    # 有効な情報タイプとそれに対応するヘッダキーの辞書
    valid_info_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }

    # 有効な情報タイプかチェック
    if info_type in valid_info_types:
        # 新しいヘッダ辞書を作成
        updated_header = header.copy()
        # ヘッダに情報を格納
        updated_header[valid_info_types[info_type]] = info_content
        return updated_header
    
    # 変更しない場合は元のヘッダ辞書を返す
    return header