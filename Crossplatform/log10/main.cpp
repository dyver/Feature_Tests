#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

void outResult(const vector<int>& result, ostream& out)
{
    out << "static int Sequence[] = {\n    ";
    for (size_t i = 0; i < result.size(); ++i) {
        out << result[i];
        if (i != result.size() - 1) out << ", ";
    }
    out << "\n};\n";
}

int main()
{
    ofstream file("./out.cpp");
    vector<int> result;
    for (int i = 10; i <= 100; i += 5) {
        result.push_back((log10(i) - 1) * (255 - 64) + 64 + 0.5);
    }
    outResult(result, cout);
    outResult(result, file);
    result.clear();
    for (int i = 100; i >= 10; i -= 5) {
        result.push_back((1 - (log10(i) - 1)) * (255 - 64) + 64 + 0.5);
    }
    outResult(result, cout);
    outResult(result, file);
    return 0;
}