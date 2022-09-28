#include <fts/fts.hpp>

#include <CLI/CLI.hpp>

#include <iostream>

int main(int argc, char **argv)
{
    CLI::App app{"App description"};

    float a = 0, b = 0;
    app.add_option("--first", a, "Parameter1");
    app.add_option("--second", b, "Parameter2");
    CLI11_PARSE(app, argc, argv);

    float result = add_floating_point_numbers(a, b);
    std::cout << result << std::endl;
    return 0;
}