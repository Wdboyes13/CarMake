
opts = " --prefix=/opt/carmake --libdir=/opt/carmake/lib --bindir=/opt/carmake/bin --includedir=/opt/carmake/include --notests"
srclink = "https://git.aubio.org/aubio/aubio"
dirname = "aubio"

package = {
    name = "Aubio",
    license = "GPL v3",
    version = "5.4.8",
    author  = "Aubio.org"
}

build = {
    "git clone --depth 1 " .. srclink,
    "cd " .. dirname,
    "./waf configure " .. opts,
    "./waf build " .. opts,
    "sudo ./waf configure " .. opts,
    "cd ..",
    "rm -rf " .. dirname
}