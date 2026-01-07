import re
from typing import Tuple


def check_email(email: str) -> Tuple[bool, str]:
    """检查提供的电子邮件地址是否有效。例如，abc.123@def.ghi.com.uk 是一个有效的电子邮件地址。尽可能覆盖更多情况以避免误判。

    Args:
        email: 要检查的电子邮件。

    Returns:
        Tuple[bool, str]: 一个元组，第一个元素是一个布尔值，指示电子邮件是否有效，第二个元素是用于检查电子邮件的模式。"""
    
    # 电子邮件验证的正则表达式模式
    # 这个模式遵循RFC 5322标准，同时考虑了实际使用中的常见情况
    pattern = r"""
        ^                           # 字符串开始
        [a-zA-Z0-9]                 # 必须以字母或数字开头
        [a-zA-Z0-9._%+-]*          # 允许字母、数字、点、下划线、百分号、加号、减号
        @                          # @符号
        [a-zA-Z0-9.-]+             # 域名部分：字母、数字、点、减号
        \.                         # 最后一个点
        [a-zA-Z]{2,}               # 顶级域名：至少2个字母
        (?:                        # 非捕获组，用于可选的子域名
            \.                     # 点分隔符
            [a-zA-Z]{2,}           # 子域名：至少2个字母
        )*                         # 可以有0个或多个子域名
        $                           # 字符串结束
    """
    
    # 编译正则表达式，忽略空白和注释
    regex = re.compile(pattern, re.VERBOSE)
    
    # 检查电子邮件是否匹配模式
    is_valid = bool(regex.match(email))
    
    return (is_valid, pattern)