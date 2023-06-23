#pragma once

#ifndef PLUGIN_NAME
#define PLUGIN_NAME "base-plugin"
#endif

struct ModuleName {
    int unknown;
    int name_length;
    char name[sizeof(PLUGIN_NAME)];
};

__attribute__((section(".nx-module-name")))
const ModuleName s_ModuleName = {.unknown = 0, .name_length = sizeof(PLUGIN_NAME), .name = PLUGIN_NAME};