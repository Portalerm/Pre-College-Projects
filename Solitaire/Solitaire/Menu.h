#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cassert>
#include<algorithm>
class Menu
{
public:
    std::string m_name;
    std::ifstream m_toRead;
    std::vector<Menu*> m_subMenus;
    Menu* m_parent;
    Menu(std::string name, std::string fileToRead) : m_name{ name }, m_toRead(fileToRead), m_subMenus(0), m_parent{ nullptr }
    {
        assert(m_toRead && "File not found!");
    }
    Menu(std::string name, std::string fileToRead, std::vector<Menu*> subMenus, Menu* parent) : m_name{ name }, m_toRead(fileToRead), m_subMenus{ subMenus }, m_parent{ parent }
    {
        assert(m_toRead && "File not found!");
    }
    Menu(std::string name, std::string fileToRead, Menu* parent) : m_name{ name }, m_toRead(fileToRead), m_subMenus(0), m_parent{ parent }
    {
        assert(m_toRead && "File not found!");
    }
    void printMenu()
    {
        system("CLS");
        while (m_toRead)
        {
            std::string line;
            std::getline(m_toRead, line);
            std::cout << line << '\n';
        }
        m_toRead.clear();
        m_toRead.seekg(0, std::ios::beg);
    }

    Menu* sub(std::string name)
    {
        auto found{ std::find_if(m_subMenus.begin(), m_subMenus.end(), [&](Menu* m) {
          return m->m_name == name;
        }) };
        if (found == m_subMenus.end())
        {
            return nullptr;
        }
        return *found;
    }
    bool hasSub(std::string name)
    {
        return sub(name) != nullptr;
    }
};