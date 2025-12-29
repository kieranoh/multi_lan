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
    # 有効な情報タイプとそれに対応するヘッダーキーのマッピング
    valid_info_types = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # 入力ヘッダーのコピーを作成（元の辞書を変更しないため）
    updated_header = header.copy()
    
    # 情報タイプが有効かチェック
    if info_type in valid_info_types:
        # 対応するヘッダーキーを取得
        header_key = valid_info_types[info_type]
        # 情報内容が空でないことを確認
        if info_content and isinstance(info_content, str):
            # ヘッダーを更新
            updated_header[header_key] = info_content
        # 情報内容が空の場合は何もしない（元のヘッダーを返す）
    
    return updated_header