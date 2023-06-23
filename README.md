# SMO-Plugin-Base

A base repository created for the [SMO-Plugin-Loader](https://github.com/CraftyBoss/SMO-Plugin-Loader). Use this repo to create plugins that are compatible with it.

# Notes

Does not work by itself as a mod for Super Mario Odyssey.

## Building

Build has only been tested on WSL2 running Ubuntu 20.04.1.

If not installed, make sure to install cmake using:
```
pip install cmake
```

Devkitpro is also required for building, follow the tutorial [Here](https://devkitpro.org/wiki/Getting_Started) to get it installed.

Make sure to install the `switch-dev` tools and libraries from devkitpro package using:
```
dkp-pacman -Sy switch-dev
```

After installing everything, Just run:
```
make
```

the make process should automatically create whats required for a successful build.

## Installing (Atmosphère)

After a successful build, Plugins should be installed in the `sd:/smo/PluginData` directory.

---

# Credits
- [exlaunch](https://github.com/shadowninja108/exlaunch/)
- [exlaunch-cmake](https://github.com/EngineLessCC/exlaunch-cmake/)
- [BDSP](https://github.com/Martmists-GH/BDSP)
- [Sanae](https://github.com/Sanae6)
- [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere)
- [oss-rtld](https://github.com/Thog/oss-rtld)
