#include <slib/stack.h>
int main()
{
    sqStack s;
    int poper, pusher[] = {5, 6, 4766, -1, 30000, -30000, 0}, count;
    printf(
        "test-stack:Creating stack s by InitStack with 7 integer elements\n");
    if (InitStack(&s, sizeof(int) * 7, sizeof(int)) == SERROR)
    {
        perror("Initstack failed");
        return 1;
    }
    printf("test-stack:Pushing integer 5, 6, 4766, -1, 30000, -30000, 0\n");
    for (count = 0; count < 7; ++count)
        Push(&s, &(pusher[count]));
    printf("test-stack:Now stack size is %d\n", GetLen(&s));
    printf("test-stack:Poping a element\n");
    Pop(&s, &poper);
    printf("test-stack:poped %d\n", poper);
    printf("test-stack:Now stack size is %d\n", GetLen(&s));
    printf("test-stack:Clearing stack\n");
    ClearStack(&s);
    printf("test-stack:Now stack size is %d\n", GetLen(&s));
    printf("test-stack:Destorying stack\n");
    DestroyStack(&s);
    return 0;
}
