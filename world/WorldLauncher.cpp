//
// Created by iku-iku-iku on 2022/10/17.
//
#include "World.h"
#include "component/RenderingComponent.h"
#include "Ring.h"
#include "object/Object.h"
using namespace core;
core::World* world;

[[maybe_unused]] static const struct Initializer {
    static void InitWorld() {
        world = (core::World*) malloc(sizeof(*world));
        world = new (world) core::World;
    }
    Initializer() {
        InitWorld();

        static Object obj[10];


        obj[0].AddComponent<RenderingComponent>()->SetShape<Ring>();
        obj[1].AddComponent<RenderingComponent>()->SetShape<Cube>();
    }
} Initializer;
