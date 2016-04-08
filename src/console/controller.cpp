#include "controller.h"
#include <string>
#include <iostream>

controller::controller(Model &_m, QObject *parent): QObject(parent), m(_m)
{
}

void controller::PluginsExist()
{
    if (!expl)
    {
        std::cout << "next plugins was found" << std::endl;
    }
    expl = true;
}

void controller::setplugdir(const char *str)
{
    m.setPluginsDir(str);
}

int controller::parse_input(int argc, char **argv)
{
    if (argc != 4 && argc != 5)
    {
        std::cout << "Usage: " << std::endl << argv[0]
             << " <in_image.bmp> <out_image.bmp> <out_result.txt>" << std::endl;
        return 0;
    }
    m.load_image(argv[1]);
    if (argc == 5 && std::strcmp(argv[4], "-filter") == 0)
    {
        m.refresh_plugins();
        if (!expl)
        {
            std::cout<< "plugins wasn't find" << std::endl;
            return 0;
        }
        std::cout << "choose plugin" <<std::endl;
        int i;
        std::cin >> i;
        m.apply_plugin(i - 1);
        return 0;
    }
    if (argc != 4)
    {
        std::cout << "Usage: " << std::endl << argv[0]
             << " <in_image.bmp> <out_image.bmp> <out_result.txt>" << std::endl;
        return 0;
    }
    try {
        m.repair_mechanism();
    } catch (const string &s) {
       std::cerr << "Error: " << s << std::endl;

    }
    return 0;
}
