#include <string.h>

/* src की सामग्री को dest में यथासंभव कॉपी करने के लिए strncpy का उपयोग करें

@param dest: गंतव्य बफर
@param dest_size: गंतव्य बफर का आकार
@param src: स्रोत बफर
@param src_size: स्रोत बफर का आकार */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // सुनिश्चित करें कि dest हमेशा null-terminated रहे
    dest[0] = '\0';
    
    // कॉपी करने के लिए वास्तविक डेटा की लंबाई निर्धारित करें
    int copy_len;
    if (src_size < 0) {
        // यदि src_size नकारात्मक है, तो src को null-terminated स्ट्रिंग मानें
        copy_len = (int)strlen(src);
    } else {
        copy_len = src_size;
    }
    
    // कॉपी की जाने वाली लंबाई dest_size-1 से अधिक नहीं होनी चाहिए (null terminator के लिए स्थान छोड़ें)
    if (copy_len > dest_size - 1) {
        copy_len = dest_size - 1;
    }
    
    // केवल तभी कॉपी करें जब copy_len सकारात्मक हो
    if (copy_len > 0) {
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';  // strncpy null termination की गारंटी नहीं देता
    }
}