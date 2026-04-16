#include "../i_video.h"
#include "../../d_main.h"

int main(int argc, char** args)
{
    printf("Starting up SRB1 C...\n");
    printf("D_SRBMain()...\n");
    D_SRBMain();
    printf("D_SRBLoop()...\n");
    D_SRBLoop();
}