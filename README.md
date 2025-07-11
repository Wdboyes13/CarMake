# This is CarMake  
__This system was built to be as simple as possible, and generate Makefiles how I would write them__  
__I got the idea, because I liked the simplicity of Rust's `cargo`__  
__And so the name, is Cargo + Make - CarMake__  
__This system is undocumented currently, since it was made only for my projects__  

## To get  
__Requirements__  
- `pkg-config`  
- `install`  
- libzstd  
- liblua
- libcurl  
  
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
If you wan't to use this in your own projects, check out [tests](/tests)  
