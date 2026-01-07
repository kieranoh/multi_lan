from urllib.parse import urlparse

def get_target_for_redirect(target: str, domain: str) -> str:
    '''检查提供的目标 URL 字符串是否在提供的域内。
如果是，则返回用于重定向的目标 URL；否则，回退到用于重定向的域 URL。
使用 https 协议。

示例：
    get_target_for_redirect('https://music.example.com', 'example.com') -> 'https://music.example.com'
    get_target_for_redirect('https://example.com/service', 'example.com') -> 'https://example.com/service'
    get_target_for_redirect('https://blog.example.com/posts', 'example.com') -> 'https://blog.example.com/posts'
    get_target_for_redirect('https://another.com', 'example.com') -> 'https://example.com'

参数：
    target (str): 目标 URL 字符串。
    domain (str): 域字符串，不带协议。

返回：
    str: 用于重定向的 URL 字符串。'''
    try:
        # 解析目标URL
        parsed_target = urlparse(target)
        
        # 检查目标URL是否在指定域内
        # 检查域名是否以指定域结尾（支持子域名）
        if parsed_target.netloc.endswith('.' + domain) or parsed_target.netloc == domain:
            # 确保使用https协议
            if parsed_target.scheme != 'https':
                # 重建URL，使用https协议
                return f"https://{parsed_target.netloc}{parsed_target.path}"
            else:
                return target
        else:
            # 目标不在指定域内，回退到域URL
            return f"https://{domain}"
    except Exception:
        # 如果解析失败或出现其他错误，回退到域URL
        return f"https://{domain}"