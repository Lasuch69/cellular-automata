# Cellular Automata
This repository contains cellular automata algorithm based on the [Cellular Automata Method for Generating Random Cave-Like Levels](https://www.roguebasin.com/index.php?title=Cellular_Automata_Method_for_Generating_Random_Cave-Like_Levels&action=info) article, and was written with C++ and GDExtension as an addon for Godot 4.1.

## Usage
### Requirements
- `Scons`
- `GCC` or `Clang`

### Build
Clone this repository:
```
git clone --recurse-submodules git@github.com:Lasuch69/cellular-automata.git
cd cellular-automata
```

Build in debug mode:
```
scons
```

Build in release mode:
```
scons target=template_release
```

Compiled library is inside `demo/bin`, you can test it by running project inside `demo` directory.
