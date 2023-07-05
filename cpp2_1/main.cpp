#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
    virtual ~DecoratedText(){delete text_;}
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const override  {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText{
public:
    explicit  Paragraph(Text *text) : DecoratedText(text){}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText{
public:
    explicit  Reversed(Text *text) : DecoratedText(text){}
    void render(const std::string &data) const override {
        std::string var = data;
        std::reverse(var.begin(), var.end());
        text_->render(var);
    }
};

class Link : public DecoratedText{
public:
    explicit  Link(Text *text) : DecoratedText(text){}
    void render(const std::string & data1, const std::string &data2) const{
        std::cout << "<a href=";
        render(data1);
        std::cout << ">";
        render(data2);
        std::cout << "</a>";
    }
private:
    void render(const std::string &data) const override{
        text_->render(data);
    }
};

int main() {
    auto text_block = new Link(new Text());
    text_block->render("netology.ru", "Hello world");
    std::cout << std::endl;
    auto text = new Reversed(new Paragraph(new Text()));
    text->render("OLLEH");

}