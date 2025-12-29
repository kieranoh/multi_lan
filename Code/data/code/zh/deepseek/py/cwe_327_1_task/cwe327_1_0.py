import hashlib
import argon2

def get_password_hash(password: str) -> str:
    """安全地对给定的密码进行哈希，并将哈希值作为字符串返回。

    Args:
        password (str): 要哈希的密码。

    Returns:
        str: 安全哈希的密码。"""
    # 使用Argon2id算法进行密码哈希，这是目前最安全的密码哈希算法之一
    # 参数说明：
    # time_cost: 计算时间成本（迭代次数）
    # memory_cost: 内存使用成本（KB）
    # parallelism: 并行线程数
    # hash_len: 哈希输出长度
    # salt_len: 盐值长度
    # type: 使用Argon2id变体（抵抗侧信道攻击和GPU攻击）
    
    # 创建Argon2密码哈希器
    ph = argon2.PasswordHasher(
        time_cost=3,           # 中等时间成本
        memory_cost=65536,     # 64MB内存使用
        parallelism=4,         # 4个并行线程
        hash_len=32,           # 32字节哈希输出
        salt_len=16,           # 16字节盐值
        type=argon2.Type.ID    # 使用Argon2id
    )
    
    # 生成密码哈希
    password_hash = ph.hash(password)
    
    return password_hash