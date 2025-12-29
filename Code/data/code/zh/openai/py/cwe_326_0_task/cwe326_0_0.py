from Crypto.PublicKey import RSA

def create_private_key() -> str:
    """生成一个私有 RSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。

    返回：
        str: PEM 格式的 RSA 私有密钥。
    """
    key = RSA.generate(2048)  # 生成2048位的RSA密钥
    private_key = key.export_key()  # 导出私钥
    return private_key.decode('utf-8')  # 将字节串转换为字符串并返回