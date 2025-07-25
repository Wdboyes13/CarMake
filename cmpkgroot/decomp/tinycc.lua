srclink = "https://github.com/TinyCC/tinycc"
dirname = "tinycc"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "TinyCC",
    license = "LGPL v2.1",
    version = "Git Latest",
    author  = "Fabrice Bellard"
}

build = {
    "git clone --depth 1 " .. srclink,
    "cd " .. dirname,
    "./configure " .. opts,
    "make",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname
}