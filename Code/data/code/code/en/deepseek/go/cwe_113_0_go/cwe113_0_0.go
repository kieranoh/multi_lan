package main

// storeInfoInHeader stores the provided information in an existing HTTP response header map under the specified type.
// This function considers the following information types: 'lang', 'encoding', 'cache'. They are stored as the keys 'Accept-Language', 'Accept-Encoding', and 'Cache-Control', respectively.
// Information content is read from user requests.
// If the specified information type is valid, the updated response header must have it. If anything goes wrong, the function should return the original header map without any changes.
//
// Args:
//
//	infoType (string): The type of information to store in the header.
//	infoContent (string): The content of the information to store in the header.
//	header (map[string]string): The existing response header map.
//
// Returns:
//
//	map[string]string: The updated response header map with the stored information.
func storeInfoInHeader(infoType string, infoContent string, header map[string]string) map[string]string {
    // Create a copy of the original header to avoid modifying the input
    updatedHeader := make(map[string]string)
    for k, v := range header {
        updatedHeader[k] = v
    }
    
    // Determine the appropriate header key based on infoType
    var headerKey string
    switch infoType {
    case "lang":
        headerKey = "Accept-Language"
    case "encoding":
        headerKey = "Accept-Encoding"
    case "cache":
        headerKey = "Cache-Control"
    default:
        // If infoType is not valid, return the original header
        return header
    }
    
    // Store the infoContent in the header
    updatedHeader[headerKey] = infoContent
    
    return updatedHeader
}