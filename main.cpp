#include "Core/World.h"

core::World world;
int main()
{
    while (world.IsGoing()) {world.Update();}
    return 0;
}