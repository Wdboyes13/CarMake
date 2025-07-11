srclink = "https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.18.tar.gz"
archname = "libiconv-1.18.tar.gz"
dirname = "libiconv-1.18"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "libiconv",
    license = "GPL v3",
    version = "1.18",
    author  = "gnu"
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