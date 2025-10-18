# Meltris
Welcome to the source code of meltris!
Meltris is a block stacking game i made to get myself familiar with the C++ ecosystem and get more low-level with OpenGL.
If you want, feel free to contribute to the project!

## Building
> [!NOTE]
> Currently i'm developing this on linux, so i can't be sure how other platforms might work

First, you need to clone the project:
```
git clone --recursive https://github.com/xMelisek/meltris
```

go into the newly created directory if you haven't so:
```
cd meltris
```

after cloning the project and its submodules, create the build files:
```
cmake -B build
```

when it finishes making the build files, build the executable!
```
cmake --build build
```

And done! you can run the executable with `./build/meltris`

## License
This project is under the zlib license.
