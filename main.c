#include "TheGame.h"

int main(void)
{
    const char* title = "My Game";
    const int screenWidht = 800;
    const int screenHeight = 600;
    const int virtualWidth = 800;
    const int virtualHeight = 600;
    const int fps = 60;

    Game *game = CreateGame(title, screenWidht, screenHeight, virtualWidth, virtualHeight, fps);
    if (game == NULL)
        return -1;

    RunGame(game);
    DestroyGame(game);

    return 0;
}
