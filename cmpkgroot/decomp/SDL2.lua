srclink = "https://github.com/libsdl-org/SDL/releases/download/release-2.32.4/SDL2-2.32.4.tar.gz"
archname = "SDL2-2.32.4.tar.gz"
dirname = "SDL2-2.32.4"

cmakeopts = "-S .. -G Ninja -DCMAKE_INSTALL_PREFIX=/opt/carmake"

package = {
    name = "SDL2",
    license = "Zlib",
    version = "2.32.4",
    author  = "SDL"
}

build = {
    "wget " .. srclink,
    "tar xzf " .. archname,
    "cd " .. dirname,
    "mkdir build",
    "cd build",
    "cmake " .. cmakeopts,
    "ninja",
    "sudo ninja install",
    "cd ../..",
    "rm -rf " .. dirname,
    "rm -f " ..archname
}