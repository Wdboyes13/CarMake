#include "common.h"

void Parse(ProjectInfo* info){
    toml_result_t result = toml_parse_file_ex(".config/tests.toml");

    toml_datum_t AuthName = toml_seek(result.toptab, "GitInfo.AuthName");
    toml_datum_t AuthMail = toml_seek(result.toptab, "GitInfo.AuthMail");

    toml_datum_t LocName = toml_seek(result.toptab, "GitInfo.LocName");
    toml_datum_t RemName = toml_seek(result.toptab, "GitInfo.RemName");

    toml_datum_t TestFolderPath = toml_seek(result.toptab, "TestInfo.TestFolderPath");
    toml_datum_t TestNames = toml_seek(result.toptab, "TestInfo.TestNames");

    if (AuthName.type != TOML_STRING)       error("Missing GitInfo.AuthName", 0);
    if (AuthMail.type != TOML_STRING)       error("Missing GitInfo.AuthMail", 0);
    if (RemName.type != TOML_STRING)       error("Missing GitInfo.RemName", 0);
    if (LocName.type != TOML_STRING)       error("Missing GitInfo.LocName", 0);
    if (TestFolderPath.type != TOML_STRING) error("Missing TestInfo.TestFolderPath", 0);
    if (TestNames.type != TOML_ARRAY)       error("Missing TestInfo.TestNames", 0);
    
    info->GitInfo.AuthMail = strdup(AuthMail.u.s);
    info->GitInfo.AuthName = strdup(AuthName.u.s);
    info->TestInfo.TestFolderPath = strdup(TestFolderPath.u.s);
    info->GitInfo.LocName = strdup(LocName.u.s);
    info->GitInfo.RemName = strdup(RemName.u.s);

    FillFlexArray(TestNames, TestInfo.TestNames);
}