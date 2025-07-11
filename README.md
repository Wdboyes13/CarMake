# This is CarMake  
__This system was built to be as simple as possible, and generate Makefiles how I would write them__  
__I got the idea, because I liked the simplicity of Rust's `cargo`__  
__And so the name, is Cargo + Make - CarMake__  
__This system is undocumented currently, since it was made only for my projects__  

## To get  
- You will need `pkg-config` to use it, since generated files rely on it  
- First Clone this repo `git clone --depth 1 https://github.com/Wdboyes13/CarMake carmake`  
- Then do `cd carmake`  
- Then build with `make`  
- And install with `make install` optionally provide `DESTDIR=[YourDir]` to change the install dir, replacing `[YourDir]` with where you want it  

## Licenses  
__[Main License](/LICENSE)__  
__[Short License](/Fileheader.txt)__  
__[libtomlc17 License](/libsrcs/tomlc17/LICENSE)__  

## To Use  
If you wan't to use this in your own projects, check out [tests/1/cm.toml](/tests/1/cm.toml)  