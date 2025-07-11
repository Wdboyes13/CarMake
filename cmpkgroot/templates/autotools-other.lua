archname = "Project.tar.gz"
srclink = "https://Link.to/Project.tar.gz"
dirname = "Project"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "LibName",
    license = "License Type",
    version = "Version",
    author  = "Author"
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