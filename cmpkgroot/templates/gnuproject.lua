archname = "Project.tar.gz"
srclink = "https://ftp.gnu.org/gnu/Project/" .. archname
dirname = "Project"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "LibName",
    license = "License Type",
    version = "Version",
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