#include "engine.h"

void render() {
    dprintf(STDOUT_FILENO, "Content-Type: text/html\\n\\n");
    #include "template.html.h"
}

int main() {
    render();
    return 0;
}
