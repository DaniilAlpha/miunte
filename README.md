# MiUnTe (Micro Unit Testing)

Plain macro zero-dependency single-file library to get rid of boilerplate testing code.

## Usage

If you want, you can just copy the library's header into your project tests and include directly.

The other way (more modular) is to use the CMake's FetchContent: 

```cmake
include(FetchContent)

# ...

FetchContent_Declare(milo
    GIT_REPOSITORY https://github.com/DaniilAlpha/miunte.git
    GIT_TAG v1.0.0 # put the tag or commit hash you want here (usually you should use the latest)
)

```
