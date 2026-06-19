#include <stdio.h>
#include <string.h>

struct message
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    struct message msg;

    // Producer
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello, message queue!");

    printf("Producer: Data sent to message queue: %s\n", msg.msg_text);

    // Consumer
    printf("Consumer: Data received from message queue: %s\n", msg.msg_text);

    return 0;
}
