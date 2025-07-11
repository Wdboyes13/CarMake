local baseurl = "https://raw.githubusercontent.com/Wdboyes13/CarMake/master/cmpkgroot/comp/"

function make_package(name)
    return {
        name = name,
        urlbase = name .. ".lua.zst",
        url = baseurl .. urlbase,
        oname = name .. ".lua"
    }
end

pkgs = {
        make_package("libmicrohttpd"),
        make_package("libevent"),
        make_package("SDL2"),
        make_package("openssl"),
        make_package("libiconv"),
        make_package("libcurl"),
        make_package("lua"),
        make_package("zstd"),
        make_package("gmp"), 
        make_package("nettle"),
        make_package("tinycc"),
        make_package("zlib")
}