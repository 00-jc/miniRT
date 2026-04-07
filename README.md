_This project has been created as part of the 42 curriculum by jaicastr, asoria_

# miniRT

## Description

A real-time mini ray-tracer, designed to be able to handle simple scenes in real time using only the CPU, relying on minilibx as little as possible.

## Instructions

To use it, first you have to compile using the following command:

```bash
make
```

But we support other targets:

- make analyze: runs gcc's and clang's static analysis
- make debug: compiles the binary in -O0 and -g3
- make sanitize: compiles the program with ASan/UBSan/LSan
- make sanitize\_threads: compiles the program with TSan
- make: compiles the binary using LTO and -march=native

Inside the code, we hint and sometimes force the compiler to use SSE/AVX/AVX2/AVX512 instructions if available, so valgrind probably won't work since it can't handle these instructionsets, please use the sanitizer runtime instead to debug/check.

> [!NOTE]
> Make sure you've fetched the submodules from the remotes.

After compilation finishes, running the program can be done by:

```bash
./miniRT <scenes/scene.rt> [width height] 
```

As the grammar suggests, width and height are completely optional, miniRT will default to a HD (720p) window to balance quality and performance.

If at any time the scene needs to be reloaded (elements changed, added elements to the scene, etc), just press `r`, miniRT keeps track of the file and will react on command to any changes, reloading the full scene instantly, if the file was destroyed or any other issue occurs during this phase, miniRT will exit gracefully.

### Create a Scene

To create a scene file,this grammar must be used:

```
# == miniRT grammar ==

<scene>         ::=<statement>* # must contain exactly one camera and one ambient
<statement>     ::=<camera> | <ambient> | <light> | <sphere> | <cylinder> | <plane> | <cone>

# == Unique objects (may appear only one time) ==

<camera>        ::="C" <ws> <coords> <ws> <coords> <ws> <uint8>
<ambient>       ::="A" <ws> <double01> <ws> <color>

# == Non-unique objects (may appear zero or more times) ==

<light>         ::="L" <ws> <coords> <ws> <double01> <ws> <color>
<sphere>        ::="sp" <ws> <coords> <ws> <double+> <ws> <color> <textures>
<cylinder>      ::="cy" <ws> <coords> <ws> <unitvec> <ws> <double+> <ws> <double+> <ws> <color> <textures>
<plane>         ::="pl" <ws> <coords> <ws> <unitvec> <ws> <color> <textures>
<cone>          ::="co" <ws> <coords> <ws> <unitvec> <ws> <double+> <ws> <double+> <ws> <color> <textures>

# == textures (optional, trailing) ==

<textures>      ::=<bmp-path>? <color-tx-path>?
<bmp-path>      ::=<ws> "MAP=" <filepath>                   # prefix 0x3D50414D
<color-tx-path> ::=<ws> "TXT=" <filepath>                   # prefix 0x3D545854
<filepath>      ::=[^ \t\n\r\f\v]+                          # non-blank characters
<coords>        ::=<double> "," <double> "," <double>
<unitvec>       ::=<coords>                                 # [0,1]
<color>         ::=<uint8> "," <uint8> "," <uint8>          # R,G,B each 0–255
<double>        ::="-"? <digits> ( "." <digits> )?
<double01>      ::=<double>                                 # value must be in [0.0, 1.0]
<double+>       ::=<double>                                 # value must be > 0
<uint8>         ::=<digits>                                 # value must be 0–255
<digits>        ::=[0-9]+
<ws>            ::=[ \t\n\r\f\v]+ # any blank
```

> [!NOTE]
> No newlines are enforced

## Resources

- `scenes/`:    contains maps available to use, each labeled to display a feature.
- `textures/`:  contains texture data available to use in any of the maps.
- `scripts/`:   contains scripts to convert and adapt any image to the expected formats using imagemagick.


### Expected depth map format (.bmp):

```c
typedef struct s_bmp_map
{
    uint64_t    width;
    uint64_t    height;
    uint8_t     data[];
}   t_bmp_map;
```

### Expected color map format (.clr):

```c
typedef struct s_clr_map
{
    uint64_t    width;
    uint64_t    height;
    uint32_t    data[]; // RGBA data, no endian assumtions
}   t_clr_map;
```

All texure files must be of size power of 2 for performance reasons, please use the files in `scripts` to prepare them.

---

> [!WARNING]
> This program uses all threads available and it uses CPU-rendering only, it will take a toll on your cpu usage.

> [!WARNING]
> This program might not compile under very old gcc/clang versions, it was designed around clang 20.1 and gcc 14.3 since warn behaviour might change accross versions. Aditionally, minilibx stopped compiling in gcc 15.0 even without warning flags.
