archname = "zlib-1.3.1.tar.gz"
srclink = "https://zlib.net/zlib-1.3.1.tar.gz"
dirname = "zlib-1.3.1"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "ZLib",
    license = "ZLib License",
    version = "1.3.1",
    author  = "ZLib"
}

build = {
    "wget " .. srclink,
    "tar xzf " .. archname,
    "cd " .. dirname,
    "./configure " .. opts,
    "make",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}