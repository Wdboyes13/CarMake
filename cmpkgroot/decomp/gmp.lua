archname = "gmp-6.3.0.tar.xz"
srclink = "https://gmplib.org/download/gmp/" .. archname
dirname = "gmp-6.3.0"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "GNU MP",
    license = "GPL v3",
    version = "6.3.0",
    author  = "gnu"
}

build = {
    "wget " .. srclink,
    "tar xf " .. archname,
    "cd " .. dirname,
    "./configure " .. opts,
    "make",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}