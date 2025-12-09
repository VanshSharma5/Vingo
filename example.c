    #include <stdio.h>

    int main(void) {
        printf("Content-Type: text/html \n\n");
        printf("<html><head><title>CGI C Example</title></head><body>");
        printf("<h1>Hello from C CGI on Fedora!</h1>");
        printf("</body></html>");
        return 0;
    }