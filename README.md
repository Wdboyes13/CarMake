# This is CarMake  
__This system was built to be as simple as possible, and generate Makefiles how I would write them__  
__I got the idea, because I liked the simplicity of Rust's `cargo`__  
__And so the name, is Cargo + Make = CarMake__  
__This system is undocumented currently, since it was made only for my projects__  

__Lines followed by !W! - means incompatible with Windows__  
## What it is
This system is  
- A `Makefile` Generator (`cm`)  
- A C Package Manager (`cmpkg`)    
- A test suite executor & Git Integrator (`repotool`) !W!  
- And a dynamic library creator tool (`sotool`) !W!  

## To get  
__Requirements__  
- `pkg-config`  
- `install`  
- [libzstd](https://github.com/facebook/zstd)   
- [liblua 5.2.4](https://www.lua.org/ftp/lua-5.2.4.tar.gz)  
- [libcurl](https://curl.se/download.html)     
- [libgit2](https://libgit2.org/)  
  
__To Build__  
- First Clone this repo `git clone --depth 1 --recurse-submodules https://github.com/Wdboyes13/CarMake carmake`  
- Then do `cd carmake`  
- Then build with `make`  
- And install with `make install` optionally provide `DESTDIR=[YourDir]` to change the install dir, replacing `[YourDir]` with where you want it  

## Licenses  
__[Main License](/LICENSE)__  
__[Short License](/Fileheader.txt)__  
__[libtomlc17 License](/libsrcs/tomlc17/LICENSE)__  

## To Use  
If you wan't to use `cm` in your own projects, check out [tests](/cm/tests) until I document it  
To use `cmpkg` do `cmpkg [packagename]` Available packages can be find at [Packages.txt](/cmpkgroot/Packages.txt)  
If you want to us `sotool` in your own projects, get info with `sotool -h` !W!   ddd
If you want to use `repotool` look in [tests](/repotool/tests) !W!  
