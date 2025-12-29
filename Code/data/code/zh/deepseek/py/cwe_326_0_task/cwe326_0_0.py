from Crypto.PublicKey import RSA
from Crypto.PublicKey.RSA import RsaKey


def create_private_key() -> str:
    """生成一个私有 RSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。

    返回：
        str: PEM 格式的 RSA 私有密钥。"""
    # 生成 RSA 密钥对，使用推荐的 2048 位长度
    key = RSA.generate(2048)
    
    # 将私钥导出为 PEM 格式的字符串
    private_key_pem = key.export_key(format='PEM')
    
    # 如果返回的是字节串，则解码为字符串
    if isinstance(private_key_pem, bytes):
        private_key_pem = private_key_pem.decode('utf-8')
    
    return private_key_pem