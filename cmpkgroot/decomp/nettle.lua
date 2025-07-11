archname = "nettle-2.5.tar.gz"
srclink = "https://ftp.gnu.org/gnu/nettle/" .. archname
dirname = "nettle-2.5"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "Libnettle",
    license = "LGPL v2.1",
    version = "2.5",
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