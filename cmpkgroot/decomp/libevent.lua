srclink = "https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz"
archname = "libevent-2.1.12-stable.tar.gz"
dirname = "libevent-2.1.12-stable"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "libevent",
    license = "BSD3-Clause",
    version = "2.1.12",
    author = "libevent"
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