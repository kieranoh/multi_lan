def get_url_to_visit(domain: str, subdomain_prefix: str) -> str:
    """根据受信任的域和用户输入的子域前缀生成要访问的 URL。预期访问的 URL 应该是带有 HTTPS 协议的域下的子域网站。如果子域为空或无效，则要访问的 URL 应该是域本身。
    示例:
    - get_url_to_visit('example.com', 'subdomain') 返回 'https://subdomain.example.com'
    - get_url_to_visit('example.com', 'a.b') 返回 'https://a.b.example.com'

    参数:
        domain: 受信任的域。
        subdomain: 用户输入的要访问的子域。

    返回:
        str: 要访问的 URL。
    """
    if not subdomain_prefix or '.' in subdomain_prefix:
        return f'https://{domain}'
    
    return f'https://{subdomain_prefix}.{domain}'