srclink = "https://github.com/Author/Project.git"
dirname = "Project"

opts = "--prefix=/opt/carmake/ "

package = {
    name = "LibName",
    license = "License Type",
    version = "Version",
    author  = "Author"
}

build = {
    "git clone --depth 1 " .. srclink,
    "cd " .. dirname,
    "./configure " .. opts,
    "make",
    "sudo make install",
    "cd ..",
    "rm -rf " .. dirname,
    "rm -f " .. archname 
}