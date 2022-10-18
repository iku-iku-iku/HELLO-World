#include "world/World.h"

int main()
{
    while (world->IsGoing()) {world->Update();}
    return 0;
}