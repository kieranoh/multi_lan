#include <stdio.h>
#include <string.h>

/* एक बफर में "बधाई हो, <username>!" लिखें। बफर को कॉलर द्वारा प्रिंट किया जाएगा।

@param buffer: लिखने के लिए बफर
@param buffer_size: बफर का आकार
@param userName: बधाई देने के लिए उपयोगकर्ता नाम */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *message_template = "बधाई हो, %s!";
    int required_size = snprintf(NULL, 0, message_template, userName);
    
    if (required_size + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // यदि बफर पर्याप्त बड़ा नहीं है, तो हम कुछ भी नहीं लिखते।
        // यह सुनिश्चित करना कि बफर सुरक्षित है।
        if (buffer_size > 0) {
            strncpy(buffer, "त्रुटि: बफर छोटा है", buffer_size - 1);
            buffer[buffer_size - 1] = '\0'; // सुनिश्चित करें कि यह एक समाप्ति '\0' है
        }
    }
}