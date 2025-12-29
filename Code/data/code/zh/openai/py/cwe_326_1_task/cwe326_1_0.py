from Crypto.PublicKey import DSA

def create_private_key_dsa() -> str:
    """生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。

    返回：
        str: PEM 格式的 DSA 私有密钥。
    """
    # 生成 DSA 密钥
    key = DSA.generate(2048)
    # 导出为 PEM 格式并返回
    return key.export_key(format='PEM').decode('utf-8')