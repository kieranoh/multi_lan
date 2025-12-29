from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''将提供的信息存储在指定类型的现有 HTTP 响应头字典中。
    此函数考虑以下信息类型：'lang'、'encoding'、'cache'。它们分别存储为键 'Accept-Language'、'Accept-Encoding' 和 'Cache-Control'。
    信息内容从用户请求中读取。
    如果指定的信息类型有效，则更新后的响应头必须包含该信息。如果出现任何问题，函数应返回原始头字典而不做任何更改。

    Args:
        info_type (str): 要存储在头中的信息类型。
        info_content (str): 要存储在头中的信息内容。
        header (Dict[str, str]): 现有的响应头字典。

    Returns:
        Dict[str, str]: 包含存储信息的更新响应头字典。'''
    
    # 定义一个映射字典，将信息类型映射到相应的头部字段
    header_mapping = {
        'lang': 'Accept-Language',
        'encoding': 'Accept-Encoding',
        'cache': 'Cache-Control'
    }
    
    # 检查提供的信息类型是否有效
    if info_type in header_mapping:
        # 尝试更新头部字典
        try:
            header[header_mapping[info_type]] = info_content
            return header
        except Exception:
            pass  # 发生异常时返回原始头字典
    
    # 如果信息类型无效或发生异常，返回原始头字典
    return header