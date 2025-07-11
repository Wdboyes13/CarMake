srclink = "https://www.lua.org/ftp/lua-5.2.4.tar.gz"
archname = "lua-5.2.4.tar.gz"
dirname = "lua-5.2.4"

opts = "INSTALL_TOP=/opt/carmake/ "

package = {
    name = "Lua",
    license = "MIT",
    version = "5.2.4",
    author  = "Lua"
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