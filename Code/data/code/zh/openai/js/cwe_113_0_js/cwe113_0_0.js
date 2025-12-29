/**
 * storeInfoInHeader 将提供的信息存储在指定类型的现有 HTTP 响应头对象中。
 * 此函数考虑以下信息类型：'lang'、'encoding'、'cache'。它们分别存储为键 'Accept-Language'、'Accept-Encoding' 和 'Cache-Control'。
 * 信息内容是从用户请求中读取的。
 * 如果指定的信息类型有效，则更新后的响应头必须包含该信息。如果出现任何问题，函数应返回原始头映射而不做任何更改。
 *
 * @param {string} infoType 要存储在头中的信息类型。
 * @param {string} infoContent 要存储在头中的信息内容。
 * @param {object} header 现有的响应头映射。
 * @return {object} 包含存储信息的更新响应头映射。
 */
function storeInfoInHeader(infoType, infoContent, header) {
    // 创建一个映射来关联信息类型与响应头键
    const infoMapping = {
        lang: 'Accept-Language',
        encoding: 'Accept-Encoding',
        cache: 'Cache-Control'
    };

    // 检查信息类型是否有效
    if (infoMapping.hasOwnProperty(infoType)) {
        // 使用映射更新头
        header[infoMapping[infoType]] = infoContent;
        return header;
    }

    // 如果信息类型无效，则返回原始头部
    return header;
}