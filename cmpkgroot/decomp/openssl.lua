srclink = "https://github.com/openssl/openssl/releases/download/OpenSSL_1_1_1u/openssl-1.1.1u.tar.gz"
archname = "openssl-1.1.1u.tar.gz"
dirname = "openssl-1.1.1u"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "OpenSSL",
    license = "Apache 2.0",
    version = "1.1.1u",
    author  = "OpenSSL"
}

build = {
    "wget " .. srclink,
    "tar xzf " .. archname,
    "cd " .. dirname,
    "./config " .. opts,
    "make",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}