#include <++cpp11.h>

// raw string literals

void RawStringLiterals() {
    std::string s1 = "classic string with escape \n";
    std::string s2 = R"(raw string without escape \n)";
    std::string s3 = R"("raw string with quotes")";
    std::string s4 = R"***("raw string with quotes and brackets")")***";
    std::string s5 = u8R"(UTF-8 string. Русские буковки)";
    std::string s6 = R"(Русские идут)";
    outHeader("raw string literals");
    outIdent();
    std::cout << s5 << std::endl;
    outIdent();
    std::cout << s6 << std::endl;
}
