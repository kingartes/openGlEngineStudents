#include "Game.h"
#include "MenuScene.h"
int main()
{
    std::cout << "start" << std::endl;
    //Game g(new SceneRealization());
    MenuScene* scene = new MenuScene();
    Game* g = new Game(scene);
    scene->setGame(g);
    g->start();

    //
    return 0;
}