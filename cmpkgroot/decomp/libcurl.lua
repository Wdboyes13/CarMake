srclink = "https://curl.se/download/curl-8.14.1.tar.gz"
archname = "curl-8.14.1.tar.gz"
dirname = "curl-8.14.1"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "libcurl",
    license = "See Source",
    version = "8.14.1",
    author = "curl"
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