srclink = "https://ftp.gnu.org/gnu/libmicrohttpd/libmicrohttpd-1.0.1.tar.gz"
archname = "libmicrohttpd-1.0.1.tar.gz"
dirname = "libmicrohttpd-1.0.1"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "libmicrohttpd",
    license = "LGPL v2.1",
    version = "1.0.1",
    author  = "gnu"
}

build = {
    "wget " .. srclink,
    "tar xzf " .. archname,
    "cd " .. dirname,
    "./configure " .. opts,
    "make -j8",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}