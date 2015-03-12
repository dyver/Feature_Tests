#include <regex> // for regular expressions

#include <++c.h>

// regular expressions

void RegularExpressions() {
    outHeader("regular expressions");
    std::string text(
        "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n"
        "<description>\n"
            "<title-info>\n"
                "<genre>det_classic</genre>\n"
                "<author>\n"
                    "<first-name>Рекс</first-name>\n"
                    "<last-name>Стаут</last-name>\n"
                "</author>\n"
                "<book-title>Отзвуки убийства</book-title>\n"
                "<date>1941</date>\n"
            "</title-info>\n"
        "</description>\n"
    );
    try {
        std::regex pattern(R"(<(book-title)>(.*?)</(\1)>)");
        std::smatch matches;
        if (std::regex_search(text, matches, pattern)) {
            outIdent();
            std::cout << "Search results:" << std::endl;
            for (const auto& item : matches) {
                outIdent();
                std::cout << item << std::endl;
            }
        }
        outIdent();
        std::cout << "Search results using iterator:" << std::endl;
        for (
            std::sregex_iterator it(begin(text), end(text), pattern);
            it != std::sregex_iterator{};
            ++it
        ) {
            for (const auto& item : (*it)) {
                outIdent();
                std::cout << item <<  std::endl;
            }
        }
    } catch (const std::regex_error& e) {
        std::cout << "regex_error caught: " << e.what() << std::endl;
    }
    outTail();
}
