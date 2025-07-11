srclink = "https://github.com/facebook/zstd/releases/download/v1.5.7/zstd-1.5.7.tar.gz"
archname = "zstd-1.5.7.tar.gz"
dirname = "zstd-1.5.7"

opts = "PREFIX=/opt/carmake/ "

package = {
    name = "ZStandard",
    license = "GPL v2",
    version = "1.5.7",
    author  = "Facebook/Meta"
}

build = {
    "wget " .. srclink,
    "tar xzf " .. archname,
    "cd " .. dirname,
    "make " .. opts,
    "sudo make install " .. opts,
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}