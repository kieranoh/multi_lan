from Crypto.PublicKey import DSA
from Crypto.Random import get_random_bytes

def create_private_key_dsa() -> str:
    """生成一个私有 DSA 密钥，使用 PEM 格式导出，并将其作为字符串返回。

    返回：
        str: PEM 格式的 DSA 私有密钥。"""
    # 生成 DSA 密钥对
    key = DSA.generate(2048)
    
    # 导出为 PEM 格式的字符串
    private_key_pem = key.export_key(format='PEM')
    
    # 如果返回的是 bytes，则解码为字符串
    if isinstance(private_key_pem, bytes):
        return private_key_pem.decode('utf-8')
    return private_key_pem