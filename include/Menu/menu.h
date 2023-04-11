#include <string>
class Menu {
protected:
    enum options;
    std::string description;
public:
    std::string getDescription();
    void setDescription(std::String data);
    options getOptions();

    Menu(options options, std::string description);
    Menu();
};